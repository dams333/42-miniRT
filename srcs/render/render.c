/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:01:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 14:26:38 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"
#include "geometric.h"

t_point canvas_to_viewport(float x, float y, float vw, float vh, float d)
{
	t_point p = {x*vw/WINDOW_WIDTH, y*vh/WINDOW_HEIGHT, d};
	return p;
}

void intersect_ray_sphere(t_point origin, t_vector ray_direction, t_sphere_object sphere, float t[2]) {
    float r = sphere.diameter / 2;
    t_vector CO = substract(origin, (t_point) {sphere.coord_x, sphere.coord_y, sphere.coord_z});

    float a = dot_product(ray_direction, ray_direction);
    float b = 2*dot_product(CO, ray_direction);
    float c = dot_product(CO, CO) - r*r;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        t[0] = INF;
		t[1] = INF;
    }
	else
	{
		t[0] = (-b + sqrt(discriminant)) / (2*a);
		t[1] = (-b - sqrt(discriminant)) / (2*a);
	}
}

int trace_ray(t_point origin, t_vector ray_direction, float t_min, float t_max, t_generic_object *objects) {
    float closest_t = t_max;
    t_generic_object *closest_object = NULL;
    //t_sphere_object closest_sphere = {0, 0, 0, 0, 0, 0, -1};

    t_generic_object *obj = objects;
	//t_sphere_object *sphere = spheres_list;

	while(obj != NULL)
	{
        if(obj->type == SPHERE)
        {
            float t[2];
            t_sphere_object *sphere = (t_sphere_object *)obj->specific_object;
            intersect_ray_sphere(origin, ray_direction, *sphere, t);
            if(t[0] > t_min && t[0] < t_max && t[0] < closest_t)
            {
                closest_t = t[0];
                closest_object = obj;
            }
            if(t[1] > t_min && t[1] < t_max && t[1] < closest_t)
            {
                closest_t = t[1];
                closest_object = obj;
            }   
        }
		obj = obj->next;
	}
    if (closest_object == NULL)
	{
        // No object was found
    	return 0; //background color
    }
    if(closest_object->type == SPHERE)
    {
        t_sphere_object *sphere = (t_sphere_object *)closest_object->specific_object;
        return encode_rgb(sphere->color_r, sphere->color_g, sphere->color_b);
    }
    else
        return 0; //Add more objects (interfaces ?)
}

void start_rays(t_generic_object *object_list, t_camera_object *camera, t_mlx *mlx)
{
    t_point origin = {camera->coord_x, camera->coord_y, camera->coord_z};

    //Viewport informations (fake screen in the scene)
    float vw = 1;
	float vh = 1;

    //Distance of the viewport from the camera (need to calculate from the FOV)
	float d = 1;

    //Parcour all the canvas (window) pixels (start from - and go to + becaus camera is centered and not at the top left of the window)
    for(int x = -WINDOW_WIDTH/2; x <= WINDOW_WIDTH/2; x++)
	{
		for(int y = -WINDOW_HEIGHT/2; y <= WINDOW_HEIGHT/2; y++)
		{
            //Convert the canvas pixel coordinates to the viewport coordinates and make a ray from the origin
			t_vector ray_direction = substract(canvas_to_viewport(x, y, vw, vh, d), origin);
            //Trace ray (limited by the big number INF) and find the color of the nearest object
			int color = trace_ray(origin, ray_direction, d, INF, object_list);
            //Put the color in the canvas pixel (Adding the WINDOW_WIDTH/2 compensing the initial offset)
            my_pixel_put(mlx, x + WINDOW_WIDTH/2, y + WINDOW_HEIGHT/2, color, false);
		}
	}
	my_pixel_put(mlx, 0, 0, 0, true);
}