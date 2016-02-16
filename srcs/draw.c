/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:20:40 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/16 16:55:22 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Index = WIDTH * y + x * e->pixel;
** ---------------------------------
** y = index / WIDTH;
** x = index % WIDTH;
*/

static void		draw_line_v(t_env *e)
{
	float	a;
	float	x;
	int		index;
	int		j;

	j = 0;
	x = X1;
	if (X2 != X1)
		a = ((float)Y2 - (float)Y1) / ((float)X2 - (float)X1);
	while (Y1 + j != Y2)
	{
		index = (Y1 + j) * WIDTH + X1;
		if (X1 > 0 && Y1 + j > 0 && X1 < WIDTH && Y1 + j < HEIGHT)
			draw_pixel(e, e->coord.color, index);
		Y1 < Y2 ? j++ : j--;
		if (X2 != X1)
		{
			x = (float)((Y1 + j) - (Y2)) / a + (float)X2;
			X1 = (int)(x * 100);
			X1 /= 100;
		}
	}
	index = (WIDTH * Y2 + X2);
	if (X2 > 0 && Y2 > 0 && X2 < WIDTH && Y2 < HEIGHT)
		draw_pixel(e, e->coord.color, index);
}

void			draw_line(t_env *e)
{
	float	a;
	float	y;
	int		index;
	int		j;

	if (ABS((Y2 - Y1)) > ABS((X2 - X1)))
	{
		draw_line_v(e);
		return ;
	}
	y = Y1;
	j = 0;
	a = ((float)Y2 - (float)Y1) / ((float)X2 - (float)X1);
	while (X1 + j != X2)
	{
		index = (WIDTH * Y1 + X1 + j);
		if (X1 + j > 0 && Y1 > 0 && X1 + j < WIDTH && Y1 < HEIGHT)
			draw_pixel(e, e->coord.color, index);
		X1 < X2 ? j++ : j--;
		y = a * (float)((X1 + j) - (X2)) + (float)Y2;
		Y1 = (int)(y * 100) / 100;
	}
	index = (WIDTH * Y2 + X2);
	if (X2 > 0 && Y2 > 0 && X2 < WIDTH && Y2 < HEIGHT)
		draw_pixel(e, e->coord.color, index);
}

static int		index_start(t_env *e)
{
	int y_start;
	int x_start;

	y_start = (HEIGHT - e->map.l_nbr * e->pixel) / 2;
	x_start = (WIDTH - e->map.l_size * e->pixel) / 2;
	X1 += x_start + e->shift_w;
	Y1 += y_start + e->shift_h;
	X2 += x_start + e->shift_w;
	Y2 += y_start + e->shift_h;
    if ((X1 < 0 && X2 < 0) || (X1 > WIDTH && X2 > WIDTH))
        return (1);
    if ((Y1 < 0 && Y2 < 0) || (Y1 > HEIGHT && Y2 > HEIGHT))
        return (1);
	return (0);
}

void			black_img(t_env *e, int width, int height)
{
	int i;
	int count;
	int y;

	y = Y1;
	i = X1 + y * WIDTH;
	while (height > 0)
	{
		count = 0;
		while (count < width)
		{
			draw_pixel(e, BLACK, i + count);
			count++;
		}
		y++;
		height--;
		i = X1 + y * WIDTH;
	}
}

int				draw_map(t_env *e)
{
	int i;

	i = 0;
	e->coord = COORD_INIT;
	black_img(e, WIDTH, HEIGHT);
	while (i < (int)e->map.v.size)
	{
		if (i % e->map.l_size != 0)
		{
			calcul(e, i - 1, i);
			if (index_start(e) == 0)
				draw_line(e);
		}
		if (i / (int)e->map.l_size != 0)
		{
			calcul(e, i - e->map.l_size, i);
			if (index_start(e) == 0)
				draw_line(e);
		}
		i++;
	}
	fps(e);
	if (mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0) == 0)
		return (1);
	return (0);
}
