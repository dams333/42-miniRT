/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:40:34 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/10 16:45:14 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTE_LIGHTING_H
# define COMPUTE_LIGHTING_H

double	compute_lighting(t_i_3d_vec *point, double ambient, t_list *lights);

#endif
