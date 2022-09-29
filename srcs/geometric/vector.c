/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:36:32 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/29 18:28:43 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometric.h"
#include <math.h>

void    from_point(t_vector *vector, t_point point1, t_point point2)
{
    vector->x = point2.x - point1.x;
    vector->y = point2.y - point1.y;
    vector->z = point2.z - point1.z;
}

double vector_length(t_vector vector)
{
    return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

t_vector normalize(t_vector vector)
{
    double length;

    t_vector result = {vector.x, vector.y, vector.z};
    length = vector_length(vector);
    if(length != 0)
    {
        result.x /= length;
        result.y /= length;
        result.z /= length;
    }
    return result;
}

void vector_add(t_vector *vector, t_vector vector_add)
{
    vector->x += vector_add.x;
    vector->y += vector_add.y;
    vector->z += vector_add.z;
}

void vector_substract(t_vector *vector, t_vector vector_substract)
{
    vector->x -= vector_substract.x;
    vector->y -= vector_substract.y;
    vector->z -= vector_substract.z;
}

t_vector substract_vector(t_vector v1, t_vector v2)
{
    t_vector result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

t_vector multiply_by_scalar(t_vector vector, double scalar)
{
    t_vector result = {vector.x * scalar, vector.y * scalar, vector.z * scalar};
    return result;
}

void divide_by_scalar(t_vector *vector, double scalar)
{
    vector->x /= scalar;
    vector->y /= scalar;
    vector->z /= scalar;
}

float dot_product(t_vector v1, t_vector v2)
{
    float result;

    result = v1.x * v2.x;
    result += v1.y * v2.y;
    result += v1.z * v2.z;
    return (result);
}

t_matrix3 matrix_mult(t_matrix3 m1, t_matrix3 m2)
{
    t_matrix3 result;

    result.a1.x = m1.a1.x * m2.a1.x + m1.a1.y * m2.a2.x + m1.a1.z * m2.a3.x;
    result.a1.y = m1.a1.x * m2.a1.y + m1.a1.y * m2.a2.y + m1.a1.z * m2.a3.y;
    result.a1.z = m1.a1.x * m2.a1.z + m1.a1.y * m2.a2.z + m1.a1.z * m2.a3.z;
    result.a2.x = m1.a2.x * m2.a1.x + m1.a2.y * m2.a2.x + m1.a2.z * m2.a3.x;
    result.a2.y = m1.a2.x * m2.a1.y + m1.a2.y * m2.a2.y + m1.a2.z * m2.a3.y;
    result.a2.z = m1.a2.x * m2.a1.z + m1.a2.y * m2.a2.z + m1.a2.z * m2.a3.z;
    result.a3.x = m1.a3.x * m2.a1.x + m1.a3.y * m2.a2.x + m1.a3.z * m2.a3.x;
    result.a3.y = m1.a3.x * m2.a1.y + m1.a3.y * m2.a2.y + m1.a3.z * m2.a3.y;
    result.a3.z = m1.a3.x * m2.a1.z + m1.a3.y * m2.a2.z + m1.a3.z * m2.a3.z;
    return (result);
}

t_vector cross_product(t_vector v1, t_vector v2)
{
    t_vector result;

    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return (result);
}

t_matrix3 rotation_matrix_from_orientation(t_vector target)
{
    t_vector base = {0, 0, 1};
    t_vector axis = cross_product(base, target);
    double angle = acos(dot_product(base, target));
    t_matrix3 result;
    result.a1.x = cos(angle) + pow(axis.x, 2) * (1 - cos(angle));
    result.a1.y = axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle);
    result.a1.z = axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle);
    result.a2.x = axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle);
    result.a2.y = cos(angle) + pow(axis.y, 2) * (1 - cos(angle));
    result.a2.z = axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle);
    result.a3.x = axis.x * axis.z * (1 - cos(angle)) - axis.y * sin(angle);
    result.a3.y = axis.y * axis.z * (1 - cos(angle)) + axis.x * sin(angle);
    result.a3.z = cos(angle) + pow(axis.z, 2) * (1 - cos(angle));
    return (result);
}

t_vector    vector_addition(t_vector v1, t_vector v2)
{
    t_vector result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return (result);
}