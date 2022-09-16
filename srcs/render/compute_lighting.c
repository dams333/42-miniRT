/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:45:48 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/13 21:09:00 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "compute_lighting.h"

static double	compute_single_lighting(t_i_3d_vec *point,
											t_light_object *cur_light);

double	compute_lighting(t_i_3d_vec *point, double ambient, t_list *lights)
{
	double			intensity;
	t_list			*cur;
	t_light_object	*cur_light;

	intensity = ambient;
	cur = lights;
	while (cur)
	{
		cur_light = (t_light_object *) cur->content;
		intensity += compute_single_lighting(point, cur_light);
		cur = cur->next;
	}
	return (intensity);
}

static double	compute_single_lighting(t_i_3d_vec *point,
											t_light_object *cur_light)
{
	double	light_spread;

	light_spread = get_light_spread(point, cur_light);
	return (cur_light->brightness_ratio / light_spread);
}

static double	get_light_spread(t_i_3d_vec *point, t_light_object *cur_light)
{
	double	light_spread;
	double	light_ray_angle;

	light_ray_angle = atan(point.y / point.x)
	light_spread = cur_light->brightness_ratio / sin(light_ray_angle);
}
