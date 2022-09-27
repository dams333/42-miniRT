/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/27 13:12:25 by dhubleur         ###   ########.fr       */
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

void	init_events(t_param *param)
{
	mlx_hook(param->mlx->win, 33, 1L << 17, &on_close_window, param);
	mlx_key_hook(param->mlx->win, &on_key_press, param);
	mlx_mouse_hook(param->mlx->win, &on_mouse_press, param);
}

static int	on_mouse_press(int code, int x, int y, void *param)
{
	t_param		*params;
	t_parsing	*parsing;

	params = (t_param *)param;
	parsing = params->parsing;
	if (code == 1)
		click_on_screen(x, y, params);
	return (0);
}

static int	on_key_press(int keycode, void *param)
{
	t_param		*params;
	t_xvar	*xvar;

	params = (t_param *)param;
	xvar = params->mlx->mlx;
	if (keycode == XK_Escape)
		mlx_loop_end(xvar);
	key_pressed(keycode, params);
	start_rays(params->parsing, params->mlx);
	return (0);
}

static int	on_close_window(void *param)
{
	t_param		*params;
	t_xvar	*xvar;

	params = (t_param *)param;
	xvar = params->mlx->mlx;
	mlx_loop_end(xvar);
	return (0);
}