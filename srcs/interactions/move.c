/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:09:03 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/27 13:12:45 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "parsing.h"
#include "geometric.h"
#include "math.h"
#include "window_props.h"
#include "events.h"

void    move(int keycode, t_param *params)
{
    t_parsing	*parsing;
    
    parsing = params->parsing;
    if(!parsing->selected)
    {
        t_vector ori = normalize((t_vector) {params->parsing->camera->orientation_x, 0, params->parsing->camera->orientation_z});
        if(keycode == XK_w)
        {
            params->parsing->camera->coord_x += ori.x * 0.1;
            params->parsing->camera->coord_z += ori.z * 0.1;
        }
        else if(keycode == XK_s)
        {
            params->parsing->camera->coord_x -= ori.x * 0.1;
            params->parsing->camera->coord_z -= ori.z * 0.1;
        }
        else if(keycode == XK_d)
        {
            params->parsing->camera->coord_x += ori.z * 0.1;
            params->parsing->camera->coord_z += ori.x * 0.1;
        }
        else if(keycode == XK_a)
        {
            params->parsing->camera->coord_x -= ori.z * 0.1;
            params->parsing->camera->coord_z -= ori.x * 0.1;
        }
        else if(keycode == XK_space)
            params->parsing->camera->coord_y -= 0.1;
        else if(keycode == XK_Shift_L)
            params->parsing->camera->coord_y += 0.1;
    }
}