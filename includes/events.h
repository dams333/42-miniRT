/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:57:09 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/26 17:42:46 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "parsing.h"
# include "mlx_int.h"
# include "geometric.h"
# include "window_props.h"

void	init_events(t_param *param);

t_generic_object *compute_intersection(t_point origin, t_vector ray_destination, float t_min, float t_max, t_parsing *parsing);
t_point canvas_to_viewport(float x, float y, float vw, float vh, float d);

#endif
