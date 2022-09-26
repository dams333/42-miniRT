/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:01:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/26 16:32:09 by dhubleur         ###   ########.fr       */
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

void intersect_ray_sphere(t_point origin, t_vector ray_destination, t_sphere_object sphere, float intersection_distance[2]) {
    float r = sphere.diameter / 2;
    t_vector sphere_origin = substract(origin, (t_point) {sphere.coord_x, sphere.coord_y, sphere.coord_z});

    float a = dot_product(ray_destination, ray_destination);
    float b = 2*dot_product(sphere_origin, ray_destination);
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

float calcul_global_lightning(t_point point, t_vector normal, t_generic_object *objects)
{
    float i = 0;
    t_generic_object *obj = objects;
    while(obj)
    {
        t_light_object *light = obj->specific_object;
        t_vector light_direction = substract((t_point) {light->coord_x, light->coord_y, light->coord_z}, point);
        float n_dot_l = dot_product(normal, light_direction);
        if(n_dot_l > 0)
        {
            i += light->brightness_ratio * n_dot_l/(vector_length(normal)*vector_length(light_direction));
        }
        obj = obj->next;
    }
    if(i > 1)
        i = 1;
    return i;
}

int trace_ray(t_point origin, t_vector ray_destination, float t_min, float t_max, t_parsing *parsing) {
    float closest_t = t_max;
    t_generic_object *closest_object = NULL;
    t_generic_object *obj = parsing->hittables;

	while(obj != NULL)
	{
        if(obj->type == SPHERE)
        {
            float intersection_distance[2];
            t_sphere_object *sphere = (t_sphere_object *)obj->specific_object;
            intersect_ray_sphere(origin, ray_destination, *sphere, intersection_distance);
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
        t_point point = add(origin, multiply_by_scalar(ray_destination, closest_t));
        t_vector normal = substract(point, (t_point) {sphere->coord_x, sphere->coord_y, sphere->coord_z});
        normal = normalize(normal);
        float lightning = calcul_global_lightning(point, normal, parsing->lights) + parsing->ambient_lightning->lightning_ratio;
        if(lightning > 1)
            lightning = 1;
        return encode_rgb(sphere->color_r * lightning, sphere->color_g * lightning, sphere->color_b * lightning);
    }
    else
        return 0;
}

float degrees_to_radian(float degrees)
{
    return degrees * M_PI / 180;
}

void start_rays(t_parsing *parsing, t_mlx *mlx)
{
    t_point origin = {parsing->camera->coord_x, parsing->camera->coord_y, parsing->camera->coord_z};

    float vw = 1;
	float vh = WINDOW_HEIGHT/(float)WINDOW_WIDTH * vw;

	float d = (vw/2.0)/tan(degrees_to_radian(parsing->camera->horizontal_fov/2.0));

    t_vector camera_orientation = {parsing->camera->orientation_x, parsing->camera->orientation_y, parsing->camera->orientation_z};
    camera_orientation = normalize(camera_orientation);
    
    t_matrix3 rotation_matrix = rotation_matrix_from_orientation(camera_orientation);

    for(int x = -WINDOW_WIDTH/2; x <= WINDOW_WIDTH/2; x++)
	{
		for(int y = -WINDOW_HEIGHT/2; y <= WINDOW_HEIGHT/2; y++)
		{
			t_point destination = matrix_mult_point(rotation_matrix, canvas_to_viewport(x, y, vw, vh, d));
            t_vector ray_destination = normalize((t_vector) {destination.x, destination.y, destination.z});
			int color = trace_ray(origin, ray_destination, d, INF, parsing);
            my_pixel_put(mlx, x + WINDOW_WIDTH/2, y + WINDOW_HEIGHT/2, color, false);
		}
	}
	my_pixel_put(mlx, 0, 0, 0, true);
}