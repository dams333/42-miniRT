/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:32:08 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/29 17:55:01 by dhubleur         ###   ########.fr       */
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
	res[0] += ambiant->lightning_ratio * obj_r;
	res[1] += ambiant->lightning_ratio * obj_g;
	res[2] += ambiant->lightning_ratio * obj_b;
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
		res[0] += light.brightness_ratio * n_dot_l * obj_r;
		res[1] += light.brightness_ratio * n_dot_l * obj_g;
		res[2] += light.brightness_ratio * n_dot_l * obj_b;
	}
}