/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:57:09 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/27 13:12:50 by dhubleur         ###   ########.fr       */
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
void    click_on_screen(int x, int y, t_param *params);
void    move(int keycode, t_param *params);
void    key_pressed(int keycode, t_param *params);

#endif
