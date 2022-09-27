/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:19:05 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/26 14:21:21 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structures.h"

int	get_split_size(char **str)
{
	int	length;

	length = 0;
	while (str[length] != NULL)
		length++;
	return (length);
}

void	free_split(char **elements)
{
	int	i;

	i = 0;
	while (elements[i] != NULL)
	{
		free(elements[i]);
		i++;
	}
	free(elements);
}

void	free_parse(t_parsing *parsing)
{
	t_generic_object	*current;
	t_generic_object	*tmp;

	free(parsing->camera);
	free(parsing->ambient_lightning);
	current = parsing->lights;
	while (current != NULL)
	{
		free(current->specific_object);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	current = parsing->hittables;
	while (current != NULL)
	{
		free(current->specific_object);
		tmp = current->next;
		free(current);
		current = tmp;
	}
}

bool	is_only_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool	get_part(char *str, int *value)
{
	if (str == NULL)
	{
		*value = 0;
		return (true);
	}
	if (!is_only_digit(str))
		return (false);
	*value = ft_atoi(str);
	return (true);
}
