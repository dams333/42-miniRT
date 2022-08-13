/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 14:26:50 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"
#include "geometric.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_generic_object	*object_list;
	t_mlx				mlx;

	object_list = NULL;
	if (parse_map(argc, argv, &object_list) != 0)
		return (1);

	t_camera_object *camera = NULL;
	t_generic_object *obj = object_list;
	while (obj != NULL)
	{
		if (obj->type == CAMERA)
		{
			camera = (t_camera_object *)obj;
			break;
		}
		obj = obj->next;
	}

	if(camera == NULL)
	{
		printf("No camera found\n");
		return (1);
	}
	if (!init_mlx(&mlx))
		return (1);
	init_events(mlx.mlx, mlx.win);

	start_rays(object_list, camera, &mlx);

	mlx_loop(mlx.mlx);
	return (0);
}
