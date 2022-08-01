/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:46:25 by jmaia             #+#    #+#             */
/*   Updated: 2022/08/01 10:08:16 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	center_camera(t_generic_object *object_list)
{
	t_point				camera_pos;
	t_generic_object	*cur_obj;

	camera_pos = get_camera_pos(object_list);
	cur_obj = object_list;
	while (cur_obj)
	{
		move_to_get_camera_centered(cur_obj);
		cur_obj = cur_obj->next;
	}
}

static t_point	get_camera_pos(t_generic_object *object_list)
{
	t_generic_object	*cur_obj;
	t_point				camera_pos;

	cur_obj = object_list;
	while (cur_obj && cur_obj->type != CAMERA)
		cur_obj = cur_obj->next;
	if (cur_obj)
		camera_pos = extract_camera_pos(cur_obj->specific_object);
	return (camera_pos);
}

static t_point	extract_camera_pos(void *specific_obj)
{
	t_camera_object	*cam;
	t_point			cam_pos;

	cam = (t_camera_object *) specific_obj;
	cam_pos.x = coord_x;
	cam_pos.y = coord_y;
	cam_pos.z = coord_z;
	return (cam_pos);
}

static void	move_to_get_camera_centered(t_generic_object *obj)
{
	
}
