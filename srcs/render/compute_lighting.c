/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:45:48 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/10 16:52:33 by jmaia            ###   ###               */
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
	(void) point;
	(void) cur_light;
}
