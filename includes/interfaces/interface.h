/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:25:37 by jmaia             #+#    #+#             */
/*   Updated: 2022/08/26 18:23:19 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

typedef struct s_interface
{
	t_interface_type	type;
	void				*(*extract)(void *);
}	t_interface;

#endif
