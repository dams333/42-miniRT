/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:01:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/15 13:04:48 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"
#include "geometric.h"

t_vector canvas_to_viewport(float x, float y, float vw, float vh, float d)
{
	t_vector p = {x*vw/WINDOW_WIDTH, y*vh/WINDOW_HEIGHT, d};
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

void add_ambiant_light(t_ambient_lightning_object *light, float lights[3])
{
    float total = light->color_r + light->color_g + light->color_b;
    lights[0] += (light->color_r / total) * light->lightning_ratio;
    lights[1] += (light->color_g / total) * light->lightning_ratio;
    lights[2] += (light->color_b / total) * light->lightning_ratio;
}

void add_light(t_light_object *light, float lights[3], float n_dot_l, t_vector normal, t_vector light_direction)
{
    float total = light->color_r + light->color_g + light->color_b;
    lights[0] += (light->color_r / total) * light->brightness_ratio * n_dot_l/(vector_length(normal)*vector_length(light_direction));
    lights[1] += (light->color_g / total) * light->brightness_ratio * n_dot_l/(vector_length(normal)*vector_length(light_direction));
    lights[2] += (light->color_b / total) * light->brightness_ratio * n_dot_l/(vector_length(normal)*vector_length(light_direction));
}

void calcul_lightning(t_point point, t_vector normal, t_generic_object *objects, float lights[3])
{
    lights[0] = 0;
    lights[1] = 0;
    lights[2] = 0;
    t_generic_object *obj = objects;
    while(obj)
    {
        if(obj->type == AMBIENT_LIGHTNING)
        {
            t_ambient_lightning_object *ambient_lightning = obj->specific_object;
            add_ambiant_light(ambient_lightning, lights);
        }
        else if(obj->type == LIGHT)
        {
            t_light_object *light = obj->specific_object;
            t_vector light_direction = substract((t_point) {light->coord_x, light->coord_y, light->coord_z}, point);
            float n_dot_l = dot_product(normal, light_direction);
            if(n_dot_l > 0)
            {
                add_light(light, lights, n_dot_l, normal, light_direction);
            }
        }
        obj = obj->next;
    }
    if(lights[0] > 1)
        lights[0] = 1;
    if(lights[1] > 1)
        lights[1] = 1;
    if(lights[2] > 1) 
        lights[2] = 1;
}

float calcul_global_lightning(t_point point, t_vector normal, t_generic_object *objects)
{
    float i = 0;
    t_generic_object *obj = objects;
    while(obj)
    {
        if(obj->type == AMBIENT_LIGHTNING)
        {
            t_ambient_lightning_object *ambient_lightning = obj->specific_object;
            i += ambient_lightning->lightning_ratio;
        }
        else if(obj->type == LIGHT)
        {
            t_light_object *light = obj->specific_object;
            t_vector light_direction = substract((t_point) {light->coord_x, light->coord_y, light->coord_z}, point);
            float n_dot_l = dot_product(normal, light_direction);
            if(n_dot_l > 0)
            {
                i += light->brightness_ratio * n_dot_l/(vector_length(normal)*vector_length(light_direction));
            }
        }
        obj = obj->next;
    }
    if(i > 1)
        i = 1;
    return i;
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
        t_point point = add(origin, multiply_by_scalar(ray_direction, closest_t));
        t_vector normal = substract(point, (t_point) {sphere->coord_x, sphere->coord_y, sphere->coord_z});
        normal = normalize(normal);
        float light[3];
        calcul_lightning(point, normal, objects, light);
        float lightning = calcul_global_lightning(point, normal, objects);
        float color_red = sphere->color_r * 0.5 * lightning + light[0] * 255 * 0.5 * lightning;
        float color_green = sphere->color_g * 0.5 * lightning + light[1] * 255 * 0.5 * lightning;
        float color_blue = sphere->color_b * 0.5 * lightning + light[2] * 255 * 0.5 * lightning;
        return encode_rgb(color_red, color_green, color_blue);
        //return encode_rgb(sphere->color_r * lightning + light[0] * 255 > 255 ? 255 : sphere->color_r * lightning + light[0] * 255, sphere->color_g * lightning + light[1] * 255 > 255 ? 255 : sphere->color_g * lightning + light[1] * 255, sphere->color_b * lightning + light[2] * 255 > 255 ? 255 : sphere->color_b * lightning + light[2] * 255);
    }
    else
        return 0; //Add more objects (interfaces ?)
}

float degrees_to_radian(float degrees)
{
    return degrees * M_PI / 180;
}

void start_rays(t_generic_object *object_list, t_camera_object *camera, t_mlx *mlx)
{
    t_point origin = {camera->coord_x, camera->coord_y, camera->coord_z};

    //Viewport informations (fake screen in the scene)
    float vw = 1;
	float vh = WINDOW_HEIGHT/(float)WINDOW_WIDTH * vw;

    //Distance of the viewport from the camera (need to calculate from the FOV)
	float d = (vw/2.0)/tan(degrees_to_radian(camera->horizontal_fov/2.0));
    //printf("d = %f\n", d);

    t_vector camera_orientation = {camera->orientation_x, camera->orientation_y, camera->orientation_z};
    camera_orientation = normalize(camera_orientation);
    //printf("camera_orientation = %f %f %f\n", camera_orientation.x, camera_orientation.y, camera_orientation.z);
    
    t_matrix3 rotation_matrix = rotation_matrix_from_orientation(camera_orientation);
    //printf("Matrix:\n");
    //printf("%f %f %f\n", rotation_matrix.a1.x, rotation_matrix.a2.x, rotation_matrix.a3.x);
    //printf("%f %f %f\n", rotation_matrix.a1.y, rotation_matrix.a2.y, rotation_matrix.a3.y);
    //printf("%f %f %f\n", rotation_matrix.a1.z, rotation_matrix.a2.z, rotation_matrix.a3.z);

    //Parcour all the canvas (window) pixels (start from - and go to + becaus camera is centered and not at the top left of the window)
    for(int x = -WINDOW_WIDTH/2; x <= WINDOW_WIDTH/2; x++)
	{
		for(int y = -WINDOW_HEIGHT/2; y <= WINDOW_HEIGHT/2; y++)
		{
            //Convert the canvas pixel coordinates to the viewport coordinates and make a ray from the origin
			t_vector ray_direction = matrix_mult_vector(rotation_matrix, canvas_to_viewport(x, y, vw, vh, d));
            //Trace ray (limited by the big number INF) and find the color of the nearest object
			int color = trace_ray(origin, ray_direction, d, INF, object_list);
            //Put the color in the window pixel (Adding the WINDOW_WIDTH/2 compensing the initial  offset)
            my_pixel_put(mlx, x + WINDOW_WIDTH/2, y + WINDOW_HEIGHT/2, color, false);
		}
	}
	my_pixel_put(mlx, 0, 0, 0, true);
}