/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/13 01:22:10 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"
#include "geometric.h"

void my_pixel_put(t_mlx *mlx_object, int x, int y, int color, bool put)
{
	int useless;

	static void *img = NULL;
	static int *data = NULL;
	if(!img || !data)
	{
		img = mlx_new_image(mlx_object->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		data = (int *)mlx_get_data_addr(img, &useless, &useless, &useless);
	}
	if(put)
	{
		mlx_put_image_to_window(mlx_object->mlx, mlx_object->win, img, 0, 0);
		mlx_destroy_image(mlx_object->mlx, img);
		img = NULL;
		data = NULL;
		return ;
	}
	if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;
	data[y * WINDOW_WIDTH + x] = color;
}

t_vector canvas_to_viewport(float x, float y, float vw, float vh, float d)
{
	t_vector p = {x*vw/WINDOW_WIDTH, y*vh/WINDOW_HEIGHT, d};
	return p;
}

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void intersect_ray_sphere(t_point origin, t_vector ray_direction, t_sphere_object sphere, int t[2]) {
    float r = sphere.diameter / 2;
    t_vector CO = substract(origin, (t_point) {sphere.coord_x, sphere.coord_y, sphere.coord_z});

    float a = dot_product(ray_direction, ray_direction);
    float b = 2*dot_product(CO, ray_direction);
    float c = dot_product(CO, CO) - r*r;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        t[0] = INF;
		t[1] = INF;
    }
	else
	{
		t[0] = (-b + sqrt(discriminant)) / (2*a);
		t[1] = (-b - sqrt(discriminant)) / (2*a);
	}
}


int trace_ray(t_point origin, t_vector ray_direction, int t_min, int t_max, t_sphere_object *spheres_list) {
    int closest_t = t_max;
    t_sphere_object closest_sphere = {0, 0, 0, 0, 0, 0, -1};
	t_sphere_object *sphere = spheres_list;
	while(sphere != NULL)
	{
		int t[2];
		intersect_ray_sphere(origin, ray_direction, *sphere, t);
		if(t[0] > t_min && t[0] < t_max && t[0] < closest_t)
		{
			closest_t = t[0];
			closest_sphere = *sphere;
		}
		if(t[1] > t_min && t[1] < t_max && t[1] < closest_t)
		{
			closest_t = t[1];
			closest_sphere = *sphere;
		}
		sphere = sphere->next;
	}
    if (closest_sphere.color_b == -1)
	{
    	return 0; //black
    }
    return encode_rgb(closest_sphere.color_r, closest_sphere.color_g, closest_sphere.color_b);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	//t_generic_object	*object_list;
	t_mlx				mlx;

	/*object_list = NULL;
	if (parse_map(argc, argv, &object_list) != 0)
		return (1);*/

	//Camera (normalized)
	t_camera_object camera = {0, 0, 0, 0, 0, 1, 53};
	
	//Viewport (screen)
	int vw = 1;
	int vh = 1;

	int d = 1;

	//Simple sphere
	t_sphere_object sphere3 = {-2, 0, 4, 2, 0, 255, 0, NULL};
	t_sphere_object sphere2 = {2, 0, 4, 2, 0, 0, 255, &sphere3};
	t_sphere_object sphere = {0, 1, 3, 2, 255, 0, 0, &sphere2};

	t_point origin = {0, 0, 0};

	if (!init_mlx(&mlx))
		return (1);
	init_events(mlx.mlx, mlx.win);

	for(int x = -WINDOW_WIDTH/2; x <= WINDOW_WIDTH/2; x++)
	{
		for(int y = -WINDOW_HEIGHT/2; y <= WINDOW_HEIGHT/2; y++)
		{
			t_vector ray_direction = canvas_to_viewport(x, y, vw, vh, d); //as camera is in 0,0,0 the vector component are the point's coordinates
			int color = trace_ray(origin, ray_direction, 1, INF, &sphere);
			my_pixel_put(&mlx, x + WINDOW_WIDTH/2, y + WINDOW_HEIGHT/2, color, false);
		}
	}
	my_pixel_put(&mlx, 0, 0, 0, true);
	

	mlx_loop(mlx.mlx);
	return (0);
}
