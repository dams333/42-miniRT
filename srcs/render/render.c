/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:01:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 18:26:24 by dhubleur         ###   ########.fr       */
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

void intersect_ray_sphere(t_point origin, t_vector ray_direction, t_sphere_object sphere, float intersection_distance[2]) {
    float r = sphere.diameter / 2;
    t_vector sphere_origin = substract(origin, (t_point) {sphere.coord_x, sphere.coord_y, sphere.coord_z});

    float a = dot_product(ray_direction, ray_direction);
    float b = 2*dot_product(sphere_origin, ray_direction);
    float c = dot_product(sphere_origin, sphere_origin) - r*r;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        // No solution -> doesnt intersect
        intersection_distance[0] = INF;
		intersection_distance[1] = INF;
    }
	else
	{
        // One or two solutions -> intersect
		intersection_distance[0] = (-b + sqrt(discriminant)) / (2*a);
		intersection_distance[1] = (-b - sqrt(discriminant)) / (2*a);
	}
}

int trace_ray(t_point origin, t_vector ray_direction, float t_min, float t_max, t_generic_object *objects) {
    float closest_t = t_max;
    t_generic_object *closest_object = NULL;
    t_generic_object *obj = objects;

	while(obj != NULL)
	{
        if(obj->type == SPHERE)
        {
            float intersection_distance[2];
            t_sphere_object *sphere = (t_sphere_object *)obj->specific_object;
            intersect_ray_sphere(origin, ray_direction, *sphere, intersection_distance);
            if(intersection_distance[0] > t_min && intersection_distance[0] < t_max && intersection_distance[0] < closest_t)
            {
                // If intersection is closer than previous one
                closest_t = intersection_distance[0];
                closest_object = obj;
            }
            if(intersection_distance[1] > t_min && intersection_distance[1] < t_max && intersection_distance[1] < closest_t)
            {
                // If intersection is closer than previous one
                closest_t = intersection_distance[1];
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
	float vh = WINDOW_WIDTH/(float)WINDOW_HEIGHT - vw;

    //Distance of the viewport from the camera (need to calculate from the FOV)
	float d = (vw/2.0)/tan(camera->horizontal_fov/2.0);

    t_vector camera_orientation = {camera->orientation_x, camera->orientation_y, camera->orientation_z};
    t_vector default_orientation = {0, 0, 1};
    t_matrix3 rotation_matrix = rotation_matrix_from_orientation(default_orientation, camera_orientation);

    //Parcour all the canvas (window) pixels (start from - and go to + becaus camera is centered and not at the top left of the window)
    for(int x = -WINDOW_WIDTH/2; x <= WINDOW_WIDTH/2; x++)
	{
		for(int y = -WINDOW_HEIGHT/2; y <= WINDOW_HEIGHT/2; y++)
		{
            //Convert the canvas pixel coordinates to the viewport coordinates and make a ray from the origin
            //printf("Canvas to viewport: %f %f %f\n", canvas_to_viewport(x, y, vw, vh, d).x, canvas_to_viewport(x, y, vw, vh, d).y, canvas_to_viewport(x, y, vw, vh, d).z);
			t_vector ray_direction = matrix_mult(rotation_matrix, canvas_to_viewport(x, y, vw, vh, d));
            //printf("Ray direction: %f %f %f\n", ray_direction.x, ray_direction.y, ray_direction.z);
            //Trace ray (limited by the big number INF) and find the color of the nearest object
			int color = trace_ray(origin, ray_direction, d, INF, object_list);
            //Put the color in the window pixel (Adding the WINDOW_WIDTH/2 compensing the initial  offset)
            my_pixel_put(mlx, x + WINDOW_WIDTH/2, y + WINDOW_HEIGHT/2, color, false);
		}
	}
	my_pixel_put(mlx, 0, 0, 0, true);
}