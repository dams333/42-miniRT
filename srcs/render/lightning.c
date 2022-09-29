/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:32:08 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/30 00:55:32 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"
#include "geometric.h"

void	calcul_ambiant_lightning(t_ambient_lightning_object *ambiant, float obj_r, float obj_g, float obj_b, float res[3])
{
	res[0] += ambiant->lightning_ratio * (ambiant->color_r / 255) * obj_r;
	res[1] += ambiant->lightning_ratio * (ambiant->color_g / 255) * obj_g;
	res[2] += ambiant->lightning_ratio * (ambiant->color_b / 255) * obj_b;
}

void	calcul_diffuse_lightning(t_point point, t_vector normal, t_light_object light, float obj_r, float obj_g, float obj_b, float res[3])
{
	float		n_dot_l;
	t_vector	light_direction;

	light_direction = substract((t_point) {light.coord_x, light.coord_y, light.coord_z}, point);
	light_direction = normalize(light_direction);
	normal = normalize(normal);
	n_dot_l = dot_product(normal, light_direction);
	if(n_dot_l > 0)
	{
		res[0] += light.brightness_ratio * (light.color_r / 255) * n_dot_l * obj_r;
		res[1] += light.brightness_ratio * (light.color_g / 255) * n_dot_l * obj_g;
		res[2] += light.brightness_ratio * (light.color_b / 255) * n_dot_l * obj_b;
	}
}

void	calcul_specular_lightning(t_point point, t_vector normal, t_light_object light, t_camera_object camera, float obj_r, float obj_g, float obj_b, float res[3])
{
	t_vector	reflected_directions;
	t_vector	light_direction;
	t_vector	eye_direction;
	float		specular_color[3];
	float		p;
	float		n;

	light_direction = substract((t_point) {light.coord_x, light.coord_y, light.coord_z}, point);
	light_direction = normalize(light_direction);
	reflected_directions = vector_addition(light_direction, multiply_by_scalar(normal, 2 * dot_product(light_direction, normal)));
	reflected_directions = normalize(reflected_directions);
	eye_direction = substract((t_point) {camera.coord_x, camera.coord_y, camera.coord_z}, point);
	eye_direction = normalize(eye_direction);
	p = 0.5;
	n = 400;
	specular_color[0] = (1 - p) * obj_r + p;
	specular_color[1] = (1 - p) * obj_g + p;
	specular_color[2] = (1 - p) * obj_b + p;
	res[0] += light.brightness_ratio * (light.color_r / 255) * powf(dot_product(reflected_directions, eye_direction), n) * specular_color[0];
	res[1] += light.brightness_ratio * (light.color_g / 255) * powf(dot_product(reflected_directions, eye_direction), n) * specular_color[1];
	res[2] += light.brightness_ratio * (light.color_b / 255) * powf(dot_product(reflected_directions, eye_direction), n) * specular_color[2];
}