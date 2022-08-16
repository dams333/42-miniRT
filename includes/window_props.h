/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_props.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:48:26 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/15 20:42:02 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_PROPS_H
# define WINDOW_PROPS_H

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 600
# define WINDOW_NAME "MiniRT"

# include "mlx.h"
# include "structures.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_mlx
{
    void	*mlx;
    void	*win;
}   t_mlx;

bool    init_mlx(t_mlx *mlx);
void my_pixel_put(t_mlx *mlx_object, int x, int y, int color, bool put);
int	encode_rgb(int red, int green, int blue);
void start_rays(t_generic_object *object_list, t_camera_object *camera, t_mlx *mlx);

#endif
