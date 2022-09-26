/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/26 17:41:10 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"
#include "geometric.h"

int list_count(t_generic_object *obj)
{
	int i = 0;
	while(obj)
	{
		i++;
		obj = obj->next;
	}
	return i;
}

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_mlx		mlx;
	t_param		param;

	parsing.camera = NULL;
	parsing.ambient_lightning = NULL;
	parsing.lights = NULL;
	parsing.hittables = NULL;
	parsing.selected = NULL;
	if (parse_map(argc, argv, &parsing) == false)
	{
		free_parse(&parsing);
		return (1);
	}

	printf("There is %i camera\n", parsing.camera == NULL ? 0 : 1);
	printf("There is %i ambient lightning\n", parsing.ambient_lightning == NULL ? 0 : 1);
	printf("There is %i lights\n", list_count(parsing.lights));
	printf("There is %i hittables\n", list_count(parsing.hittables));
	if (!init_mlx(&mlx))
		return (1);
	param.mlx = &mlx;
	param.parsing = &parsing;
	init_events(&param);
	
	start_rays(&parsing, &mlx);
	mlx_loop(mlx.mlx);

	free_parse(&parsing);
	return (0);
}
