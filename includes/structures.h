/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:43:56 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/04 16:36:58 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_object_type
{
	CAMERA,
	AMBIENT_LIGHTNING,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_generic_object
{
	t_object_type			type;
	void					*specific_object;
	struct s_generic_object	*next;
}	t_generic_object;

typedef struct s_ambient_lightning_object
{
	double	lightning_ratio;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_ambient_lightning_object;

typedef struct s_camera_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	orientation_x;
	double	orientation_y;
	double	orientation_z;
	int		horizontal_fov;
}	t_camera_object;

typedef struct s_light_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	brightness_ratio;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_light_object;

typedef struct s_sphere_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	diameter;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_sphere_object;

typedef struct s_plane_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	orientation_x;
	double	orientation_y;
	double	orientation_z;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_plane_object;

typedef struct s_cylinder_object
{
	double	coord_x;
	double	coord_y;
	double	coord_z;
	double	orientation_x;
	double	orientation_y;
	double	orientation_z;
	double	diameter;
	double	height;
	int		color_r;
	int		color_g;
	int		color_b;
}	t_cylinder_object;

#endif
