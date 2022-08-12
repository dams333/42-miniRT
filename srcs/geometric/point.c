/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:38:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 00:09:40 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"
#include <math.h>

double distance(t_point point1, t_point point2)
{
    return (sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2)));
}

t_vector substract(t_point point1, t_point point2)
{
    t_vector p;
    p.x = point1.x - point2.x;
    p.y = point1.y - point2.y;
    p.z = point1.z - point2.z;
    return (p);
}