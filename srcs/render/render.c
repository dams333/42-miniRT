/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:20:14 by jmaia             #+#    #+#             */
/*   Updated: 2022/09/03 20:22:45 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	render_pixel(t_img *canvas, int x, int y);

void	render(t_img *canvas)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			
			x++;
		}
		y++;
	}
}

static void	render_pixel(t_img *canvas, int x, int y)
{
	
}
