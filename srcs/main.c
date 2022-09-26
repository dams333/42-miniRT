/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/26 16:14:17 by dhubleur         ###   ########.fr       */
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
	t_parsing	parsing;
	t_mlx		mlx;

	parsing.camera = NULL;
	parsing.ambient_lightning = NULL;
	parsing.lights = NULL;
	parsing.hittables = NULL;
	if (parse_map(argc, argv, &parsing) == false)
	{
		free_parse(&parsing);
		return (1);
	}

	if (!init_mlx(&mlx))
		return (1);
	init_events(mlx.mlx, mlx.win);
	mlx_loop(mlx.mlx);

	free_parse(&parsing);
	return (0);
}
