/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera_to_z.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:50:33 by jmaia             #+#    #+#             */
/*   Updated: 2022/08/30 19:59:53 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A call to this function assume that camera's pos is (0;0)
void	rotate_camera_to_z(t_i_3d_vec camera_vec, t_list *pos)
{
	t_list		*cur;
	t_i_3d_vec	*cur_pos;

	cur = pos;
	while (*cur)
	{
		cur_pos = (t_i_3d_vec *) pos->content;
		rotate_object(cur_pos, camera_vec);
		cur = cur->next;
	}
}

static void	rotate_object(t_i_3d_vec *pos, t_i_3d_vec camera_vec)
{
	// Ici faut appliquer ce qui est noté dans le carnet magique
}

static double	get_distance(double x1, double y1, double x2, double y2)
{
	double	delta_x;
	double	delta_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

static double	get_angle(double x, double y)
{
	
}
