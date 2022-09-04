/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:38:47 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/04 16:34:18 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/i_position.h"
#include "libft.h"

static void	move_object(t_i_3d_vec *pos, t_i_3d_vec camera_pos);

void	center_camera(t_i_3d_vec camera_pos, t_list *pos)
{
	t_list			*cur;
	t_i_3d_vec		*cur_pos;

	cur = pos;
	while (cur)
	{
		cur_pos = (t_i_3d_vec *) pos->content;
		move_object(cur_pos, camera_pos);
		cur = cur->next;
	}
}

static void	move_object(t_i_3d_vec *pos, t_i_3d_vec camera_pos)
{
	*pos->x -= *camera_pos.x;
	*pos->y -= *camera_pos.y;
	*pos->z -= *camera_pos.z;
}
