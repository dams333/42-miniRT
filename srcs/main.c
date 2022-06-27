/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/06/27 14:00:13 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "render.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_generic_object	*object_list;
	t_mlx				mlx;

	object_list = NULL;
	if(parse_map(argc, argv, &object_list) != 0)
		return (1);
	if(!init_mlx(&mlx))
		return (1);
	while(1)
		;
	return (0);
}