/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/26 16:42:27 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysymdef.h>

#include "mlx.h"
#include "mlx_int.h"
#include "parsing.h"

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
	if (code == 1)
	{
		printf("Clicked in %i %i\n", x, y);
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