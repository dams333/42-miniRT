/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:18:39 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/12 16:53:03 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "checkerboard.h"
#include "mlx.h"

t_texture	load_map(t_mlx *mlx, char *file)
{
	t_texture	texture;
	void		*img;
	int			unused;

	texture.data = NULL;
	img = mlx_xpm_file_to_image(mlx->mlx, file, &(texture.width),
			&(texture.height));
	if (img == NULL)
		return (texture);
	texture.data = (int *)mlx_get_data_addr(img, &unused, &unused, &unused);
	return (texture);
}

t_matrix3	create_tbn_matrix(t_vector object_normal)
{
	t_matrix3	tbn;
	t_vector	t;
	t_vector	b;

	cross_product(&t, object_normal, (t_vector){0, 0, 1});
	if (t.x == 0 && t.y == 0 && t.z == 0)
		cross_product(&t, object_normal, (t_vector){0, 1, 0});
	normalize(&t);
	cross_product(&b, object_normal, t);
	normalize(&b);
	tbn.a1.x = t.x;
	tbn.a2.x = t.y;
	tbn.a3.x = t.z;
	tbn.a1.y = b.x;
	tbn.a2.y = b.y;
	tbn.a3.y = b.z;
	tbn.a1.z = object_normal.x;
	tbn.a2.z = object_normal.y;
	tbn.a3.z = object_normal.z;
	return (tbn);
}

void	perturb_normal(t_params *params, t_obj_intersection intersection,
	t_vector *normal)
{
	static t_texture	texture = {NULL, 0, 0};
	t_point2d			board_pos;
	int					map_color;
	t_vector			colors;
	t_vector			normal_map;

	if (texture.data == NULL)
		texture = load_map(params->mlx, "moon_normal_map.xpm");
	if (texture.data == NULL)
		return ;
	board_pos = to_checkerboard_pos(intersection.intersected,
			intersection.intersection);
	board_pos.x = (int)(board_pos.x * texture.width) % texture.width;
	board_pos.y = (int)(board_pos.y * texture.height) % texture.height;
	map_color = texture.data[(int)(board_pos.y * texture.width + board_pos.x)];
	colors.x = (double)((map_color & 0xFF0000) >> 16) / 255.0;
	colors.y = (double)((map_color & 0xFF00) >> 8) / 255.0;
	colors.z = (double)((map_color & 0xFF)) / 255.0;
	normalize(&colors);
	normal_map = (t_vector){2 * colors.x - 1,
		2 * colors.y - 1, 2 * colors.z - 1};
	*normal = matrix_mult(create_tbn_matrix(*normal), normal_map);
	normalize(normal);
}