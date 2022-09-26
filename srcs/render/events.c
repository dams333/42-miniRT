/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/26 16:58:52 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysymdef.h>

#include "mlx.h"
#include "mlx_int.h"
#include "parsing.h"
#include "geometric.h"
#include "math.h"
#include "window_props.h"
#include "events.h"

static int	on_key_press(int keycode, void *param);
static int	on_close_window(void *param);
static int	on_mouse_press(int code, int x, int y, void *param);

void	init_events(t_xvar *xvar, t_win_list *win, t_parsing *parsing)
{
	mlx_hook(win, 33, 1L << 17, &on_close_window, xvar);
	mlx_key_hook(win, &on_key_press, xvar);
	mlx_mouse_hook(win, &on_mouse_press, parsing);
}

static int	on_mouse_press(int code, int x, int y, void *param)
{
	t_parsing	*parsing;

	parsing = (t_parsing *)param;
	t_point origin = {parsing->camera->coord_x, parsing->camera->coord_y, parsing->camera->coord_z};
	float vw = 1;
	float vh = WINDOW_HEIGHT/(float)WINDOW_WIDTH * vw;
	float d = (vw/2.0)/tan(degrees_to_radian(parsing->camera->horizontal_fov/2.0));
	t_vector camera_orientation = {parsing->camera->orientation_x, parsing->camera->orientation_y, parsing->camera->orientation_z};
    camera_orientation = normalize(camera_orientation);
    
    t_matrix3 rotation_matrix = rotation_matrix_from_orientation(camera_orientation);
	if (code == 1)
	{
		float transform_x = x-WINDOW_WIDTH/2;
		float transform_y = y-WINDOW_HEIGHT/2;
		t_point destination = matrix_mult_point(rotation_matrix, canvas_to_viewport(transform_x, transform_y, vw, vh, d));
        t_vector ray_destination = normalize((t_vector) {destination.x, destination.y, destination.z});
		t_generic_object *hitted = compute_intersection(origin, ray_destination, d, INF, parsing);
		parsing->selected = NULL;
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
	return (0);
}

static int	on_key_press(int keycode, void *param)
{
	t_xvar	*xvar;

	xvar = (t_xvar *) param;
	if (keycode == XK_Escape)
		mlx_loop_end(xvar);
	return (0);
}

static int	on_close_window(void *param)
{
	t_xvar	*xvar;

	xvar = (t_xvar *) param;
	mlx_loop_end(xvar);
	return (0);
}