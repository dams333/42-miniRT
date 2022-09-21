/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c_a_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:41:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/21 17:50:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_camera(char **args, t_parsing *parsing)
{
	t_camera_object *obj;
	
	if(parsing->camera != NULL)
	{
		ft_putendl_fd("Error\nThere is more than one camera in the scene", 2);
		return (false);
	}
	if (get_split_size(args) != 4)
	{
		ft_putendl_fd("Error\nImpossible to parse camera because argument's count is not 4", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(t_camera_object));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_three_floats(args[1], &(obj->coord_x), &(obj->coord_y), &(obj->coord_z)))
	{
		free(obj);
		return (false);
	}
	if (!parse_three_floats(args[2], &(obj->orientation_x), &(obj->orientation_y), &(obj->orientation_z)))
	{
		free(obj);
		return (false);
	}
	if (obj->orientation_x < -1 || obj->orientation_x > 1 || obj->orientation_y < -1 || obj->orientation_y > 1 || obj->orientation_z < -1 || obj->orientation_z > 1)
	{
		ft_putendl_fd("Error\nImpossible to parse camera because one composant of the orientation vector is not in [-1;1]", 2);
		free(obj);
		return (false);
	}
	if (!parse_int(args[3], &(obj->horizontal_fov)))
	{
		free(obj);
		return (false);
	}
	if (obj->horizontal_fov < 0 || obj->horizontal_fov > 180)
	{
		ft_putendl_fd("Error\nImpossible to parse camera because FOV is not in [0;180]", 2);
		free(obj);
		return (false);
	}
	parsing->camera = obj;
	return (true);
}

bool	parse_ambient_lightning(char **args, t_parsing *parsing)
{
	t_ambient_lightning_object *obj;

	if(parsing->ambient_lightning != NULL)
	{
		ft_putendl_fd("Error\nThere is more than one ambient lightning in the scene", 2);
		return (false);
	}
	if (get_split_size(args) != 3)
	{
		ft_putendl_fd("Error\nImpossible to parse ambient lightning because argument's count is not 3", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(t_ambient_lightning_object));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_float(args[1], &(obj->lightning_ratio)))
	{
		free(obj);
		return (false);
	}
	if (obj->lightning_ratio < 0 || obj->lightning_ratio > 1)
	{
		ft_putendl_fd("Error\nImpossible to parse ambient lightning because lightning ration is not in [0;1]", 2);
		free(obj);
		return (false);
	}
	if (!parse_three_ints(args[2], &(obj->color_r), &(obj->color_g), &(obj->color_b)))
	{
		free(obj);
		return (false);
	}
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0 || obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		ft_putendl_fd("Error\nImpossible to parse ambient lightning because one of the color composant in not in [0;255]", 2);
		free(obj);
		return (false);
	}
	parsing->ambient_lightning = obj;
	return (true);
}

bool	parse_light(char **args, t_parsing *parsing)
{
	t_light_object *obj;

	if (get_split_size(args) != 4)
	{
		ft_putendl_fd("Error\nImpossible to parse light because argument's count is not 4", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(t_light_object));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_three_floats(args[1], &(obj->coord_x), &(obj->coord_y), &(obj->coord_z)))
	{
		free(obj);
		return (false);
	}
	if (!parse_float(args[2], &(obj->brightness_ratio)))
	{
		free(obj);
		return (false);
	}
	if (obj->brightness_ratio < 0 || obj->brightness_ratio > 1)
	{
		ft_putendl_fd("Error\nImpossible to parse light because brightness ration is not in [0;1]", 2);
		free(obj);
		return (false);
	}
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g), &(obj->color_b)))
	{
		free(obj);
		return (false);
	}
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0 || obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		ft_putendl_fd("Error\nImpossible to parse light because one of the color composant in not in [0;255]", 2);
		free(obj);
		return (false);
	}
	if (!add_item_to_list(&(parsing->lights), obj, LIGHT))
	{
		free(obj);
		return (false);
	}
	return (true);
}