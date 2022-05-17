/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:33:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/17 13:41:11 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

int		parse_map(int argc, char **argv);
bool	parse_float(char *str, float *value);
bool	parse_int(char *str, int *value);
int		get_split_size(char **str);

bool	parse_camera(char **args);

#endif