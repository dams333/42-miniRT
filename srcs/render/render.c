/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:20:14 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/04 20:41:47 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"

#include "structures.h"

static t_list	*extract_spheres(t_generic_object *object_list);
static void		render_pixel(t_img *canvas, int c_x, int c_y, t_list *spheres);
static double	calc_delta(double v_x, double v_y, double v_z, t_sphere_object *s);
static void		put_pixel(t_img *canvas, int x, int y, int r, int g, int b);

void	render(t_img *canvas, t_generic_object *object_list)
{
	int		x;
	int		y;
	t_list	*spheres;

	x = 0;
	y = 0;
	spheres = extract_spheres(object_list);
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			render_pixel(canvas, x, y, spheres);
			x++;
		}
		y++;
	}
}

static t_list	*extract_spheres(t_generic_object *object_list)
{
	t_list				*spheres;
	t_list				*sphere_wrapper;
	t_generic_object	*cur;

	spheres = 0;
	cur = object_list;
	while (cur)
	{
		if (cur->type == SPHERE)
		{
			sphere_wrapper = ft_lstnew(cur->specific_object);
			ft_lstadd_front(&spheres, sphere_wrapper);
		}
		cur = cur->next;
	}
	return (spheres);
}

static void	render_pixel(t_img *canvas, int c_x, int c_y, t_list *spheres) // Spheres need to be replaced
{
	double			v_x;
	double			v_y;
	t_list			*cur;
	t_sphere_object	*cur_sphere;
	double			delta;

	v_x = 1.0 * c_x / canvas->width;
	v_y = 1.0 * c_y / canvas->height;
	cur = spheres;
	while (cur)
	{
		cur_sphere = (t_sphere_object *) cur->content;
		delta = calc_delta(v_x, v_y, 1, cur_sphere);
		if (delta > 0)
			put_pixel(canvas, c_x, c_y, 0, 0, 0);
		else
			put_pixel(canvas, c_x, c_y, 1, 0, 0);
		cur = cur->next;
	}
}

static double	calc_delta(double v_x, double v_y, double v_z, t_sphere_object *s)
{
	double	a;
	double	b;
	double	c;

	a = pow(v_x, 2) + pow(v_y, 2) + pow(v_z, 2);
	b = -2 * (v_x * s->coord_x + v_y * s->coord_y + v_z * s->coord_z);
	c = pow(s->coord_x, 2) + pow(s->coord_y, 2) + pow(s->coord_z, 2) - pow(s->diameter / 2, 2);
	
	return (pow(b, 2) - 4 * a * c);
}

static void	put_pixel(t_img *canvas, int x, int y, int r, int g, int b)
{
	char	*data;
	int		junk;

	(void) r;
	(void) g;
	(void) b;
	data = (char *) mlx_get_data_addr(canvas, &junk, &junk, &junk);
	data[(y * canvas->width + x) * 4 + 0] = 0x00;
	data[(y * canvas->width + x) * 4 + 1] = 0x00;
	if (x == 0)
		data[(y * canvas->width + x) * 4 + 2] = 0xFF;
	else
		data[(y * canvas->width + x) * 4 + 2] = 0x00;
	data[(y * canvas->width + x) * 4 + 3] = 0x00;
}
