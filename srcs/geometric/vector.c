/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:36:32 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 21:01:05 by dhubleur         ###   ########.fr       */
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

void multiply_by_scalar(t_vector *vector, double scalar)
{
    vector->x *= scalar;
    vector->y *= scalar;
    vector->z *= scalar;
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

t_vector matrix_mult(t_matrix3 matrix, t_vector vector)
{
    t_vector result ;
    vector = normalize(vector);
    result.x = matrix.a1.x * vector.x + matrix.a2.x * vector.y + matrix.a3.x * vector.z;
    result.y = matrix.a1.y * vector.x + matrix.a2.y * vector.y + matrix.a3.y * vector.z;
    result.z = matrix.a1.z * vector.x + matrix.a2.z * vector.y + matrix.a3.z * vector.z;
    return (normalize(result));
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
    double angle_x = acos(dot_product(base, target) / (vector_length(base) * vector_length(target)));
    t_vector cross = cross_product(base, target);
    double angle_y = acos(dot_product(cross, target) / (vector_length(cross) * vector_length(target)));
    t_vector cross2 = cross_product(target, cross);
    double angle_z = acos(dot_product(cross2, target) / (vector_length(cross2) * vector_length(target)));
    t_matrix3 result;
    result.a1.x = cos(angle_x);
    result.a1.y = -sin(angle_x);
    result.a1.z = 0;
    result.a2.x = sin(angle_x);
    result.a2.y = cos(angle_x);
    result.a2.z = 0;
    result.a3.x = 0;
    result.a3.y = 0;
    result.a3.z = 1;
    return (result);
}