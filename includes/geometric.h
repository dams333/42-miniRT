/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:35:07 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 20:38:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRIC_H
# define GEOMETRIC_H

#define INF 1000000

typedef struct s_point
{
    double x;
    double y;
    double z;
}   t_point;

double distance(t_point point1, t_point point2);


typedef struct s_vector
{
    double		x;
    double		y;
    double		z;
}   t_vector;

typedef struct s_matrix3
{
    t_vector a1;
    t_vector a2;
    t_vector a3;
}   t_matrix3;

double vector_length(t_vector vector);
t_vector normalize(t_vector vector);
void vector_add(t_vector *vector, t_vector vector_add);
void vector_substract(t_vector *vector, t_vector vector_substract);
void multiply_by_scalar(t_vector *vector, double scalar);
void divide_by_scalar(t_vector *vector, double scalar);
t_vector substract(t_point point1, t_point point2);
float dot_product(t_vector v1, t_vector v2);
t_vector matrix_mult(t_matrix3 matrix, t_vector vector);
t_matrix3 rotation_matrix_from_orientation(t_vector from, t_vector to);

#endif