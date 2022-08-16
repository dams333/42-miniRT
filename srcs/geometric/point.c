/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:38:43 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/17 00:10:26 by dhubleur         ###   ########.fr       */
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

t_point add(t_point p, t_vector v)
{
    t_point result;
    result.x = p.x + v.x;
    result.y = p.y + v.y;
    result.z = p.z + v.z;
    return (result);
}

t_point matrix_mult_point(t_matrix3 matrix, t_point point)
{
    t_point result;
    result.x = matrix.a1.x * point.x + matrix.a2.x * point.y + matrix.a3.x * point.z;
    result.y = matrix.a1.y * point.x + matrix.a2.y * point.y + matrix.a3.y * point.z;
    result.z = matrix.a1.z * point.x + matrix.a2.z * point.y + matrix.a3.z * point.z;
    return (result);
}