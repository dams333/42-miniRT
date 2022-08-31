/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera_to_z.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:50:33 by jmaia             #+#    #+#             */
/*   Updated: 2022/08/31 11:25:31 by jmaia            ###   ###               */
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
	double	dist;
	double	point_angle;
	double	rotate_angle;
	double	new_angle;

	dist = get_distance(0, 0, *pos->x, *pos->y);
	point_angle = get_angle(*pos->x, *pos->y);
	rotate_angle = get_angle(*camera_vec.x, *camera_vec.y);
	new_angle = point_angle + rotate_angle;
	*pos->x = cos(new_angle) * dist;
	*pos->y = sin(new_angle) * dist;
	// Il reste plus qu'à le refaire encore une fois sur le 2e axe pour l'avoir en 3D
	// Et en vrai pour ça, go faire une fonction qui rotate toujours en 2D et appeler 2 fois cette fonction ici
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
	double	base_angle;

	base_angle = atan(abs(y) / abs(x));
	if (x > 0 && y > 0)
		return (base_angle);
	if (x < 0 && y > 0)
		return (PI - base_angle);
	if (x < 0 && y < 0)
		return (PI + base_angle);
	if (x > 0 && y < 0)
		return (2*PI - base_angle);
}
