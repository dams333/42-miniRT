/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/06 16:33:52 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

#include "events.h"
#include "i_position.h"
#include "parsing.h"
#include "window_props.h"

void	render(t_img	*canvas, t_generic_object *object_list);
static void	fill_camera_pos(t_i_3d_vec *camera_pos, t_generic_object *object_list);
static void	fill_camera_vec(t_i_3d_vec *camera_vec, t_generic_object *object_list);
static void	fill_pos(t_list **pos, t_generic_object *object_list);

void	center_camera(t_i_3d_vec camera_pos, t_list *pos);
void	rotate_camera_to_z(t_i_3d_vec camera_vec, t_list *pos);

int	main(int argc, char **argv)
{
	t_generic_object	*object_list;
	t_mlx				mlx;

	object_list = NULL;
	if (parse_map(argc, argv, &object_list) != 0)
		return (1);
	if (!init_mlx(&mlx))
		return (1);
	init_events(mlx.mlx, mlx.win);
	// TMP
	
	t_img		*img;
	t_i_3d_vec	camera_pos;
	t_i_3d_vec	camera_vec;
	t_list		*pos;

	fill_camera_pos(&camera_pos, object_list);
	fill_camera_vec(&camera_vec, object_list);
	fill_pos(&pos, object_list);
	center_camera(camera_pos, pos);
	rotate_camera_to_z(camera_vec, pos);
	img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	render(img, object_list);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img, 0, 0);

	// TMP
	mlx_loop(mlx.mlx);
	return (0);
}

// TMP jusqu'en bas
static void	fill_camera_pos(t_i_3d_vec *camera_pos, t_generic_object *object_list)
{
	t_generic_object	*cur;
	t_camera_object		*cam;

	cur = object_list;
	while (cur)
	{
		if (cur->type == CAMERA)
		{
			cam = (t_camera_object *) cur->specific_object;
			camera_pos->x = &cam->coord_x;
			camera_pos->y = &cam->coord_y;
			camera_pos->z = &cam->coord_z;
			return;
		}
		cur = cur->next;
	}
}

static void	fill_camera_vec(t_i_3d_vec *camera_vec, t_generic_object *object_list)
{
	t_generic_object	*cur;
	t_camera_object		*cam;

	cur = object_list;
	while (cur)
	{
		if (cur->type == CAMERA)
		{
			cam = (t_camera_object *) cur->specific_object;
			camera_vec->x = &cam->orientation_x;
			camera_vec->y = &cam->orientation_y;
			camera_vec->z = &cam->orientation_z;
			return;
		}
		cur = cur->next;
	}
}

static void	fill_pos(t_list **pos, t_generic_object *object_list)
{
	t_generic_object	*cur;
	t_sphere_object		*sp;
	t_i_3d_vec			*tmp_pos;
	t_list				*tmp;

	*pos = 0;
	cur = object_list;
	while (cur)
	{
		if (cur->type == SPHERE)
		{
			sp = (t_sphere_object *) cur->specific_object;
			tmp_pos = malloc(sizeof(*tmp_pos));
			tmp_pos->x = &sp->coord_x;
			tmp_pos->y = &sp->coord_y;
			tmp_pos->z = &sp->coord_z;
			tmp = ft_lstnew(tmp_pos);
			ft_lstadd_front(pos, tmp);
		}
		cur = cur->next;
	}
}
