/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:05:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/27 15:26:47 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "parsing.h"
#include "geometric.h"
#include "math.h"
#include "window_props.h"
#include "events.h"

void    click_on_screen(int x, int y, t_param *params)
{
    t_parsing	*parsing;
    
    parsing = params->parsing;
    t_point origin = {parsing->camera->coord_x, parsing->camera->coord_y, parsing->camera->coord_z};
	float vw = 1;
	float vh = WINDOW_HEIGHT/(float)WINDOW_WIDTH * vw;
	float d = (vw/2.0)/tan(degrees_to_radian(parsing->camera->horizontal_fov/2.0));
	t_vector camera_orientation = {parsing->camera->orientation_x, parsing->camera->orientation_y, parsing->camera->orientation_z};
    camera_orientation = normalize(camera_orientation);
    t_matrix3 rotation_matrix = rotation_matrix_from_orientation(camera_orientation);
    float transform_x = x-WINDOW_WIDTH/2;
	float transform_y = y-WINDOW_HEIGHT/2;
	t_point destination = matrix_mult_point(rotation_matrix, canvas_to_viewport(transform_x, transform_y, vw, vh, d));
    t_vector ray_destination = normalize((t_vector) {destination.x, destination.y, destination.z});
	t_generic_object *hitted = compute_intersection(origin, ray_destination, d, INF, parsing);
	if(hitted != NULL)
	{
		if(hitted->type == SPHERE)
		{
			t_sphere_object *sphere = (t_sphere_object *)hitted->specific_object;
			printf("Selected sphere of color %i;%i;%i\n", sphere->color_r, sphere->color_g, sphere->color_b);
			parsing->selected = hitted;
		}
	};
}

void    key_pressed(int keycode, t_param *params)
{
	if(keycode == XK_q)
	{
		printf("Unselected object\n");
		params->parsing->selected = NULL;
	}
    if(keycode == XK_w || keycode == XK_a || keycode == XK_s || keycode == XK_d || keycode == XK_space || keycode == XK_Shift_L)
        move(keycode, params);
}