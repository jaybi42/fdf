/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:54:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/15 18:03:19 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static unsigned int const	g_digits[10] = {
	0b1110111,
	0b0000011,
	0b0111110,
	0b0011111,
	0b1001011,
	0b1011101,
	0b1101101,
	0b0010011,
	0b1111111,
	0b1011111,
};

static t_coord	const g_segments_delta[7] = {
	{8, 8, 8, 16, 42},
	{8, 0, 8, 8, 42},
	{0, 16, 8, 16, 42},
	{0, 8, 8, 8, 42},
	{0, 0, 8, 0, 42},
	{0, 8, 0, 16, 42},
	{0, 0, 0, 8, 42},
};

static void	seg_aff(t_env *e, int unit)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (((unit >> i) & 1) == 1)
		{
			e->coord.x1 = e->time.x + g_segments_delta[i].x1;
			e->coord.y1 = e->time.y + g_segments_delta[i].y1;
			e->coord.x2 = e->time.x + g_segments_delta[i].x2;
			e->coord.y2 = e->time.y + g_segments_delta[i].y2;
			draw_line(e);
		}
		i++;
	}
}

static void	aff_fps(t_env *e, int unit, int shift)
{
	int x_shift;
	int y_shift;

	x_shift = 30 - shift * 12;
	y_shift = -8;
	e->time.y = SQUARE_FPS / 2 + y_shift;
	if (e->time.pos == 0)
		e->time.x = SQUARE_FPS / 2 + x_shift;
	else if (e->time.pos == 1)
		e->time.x = WIDTH - SQUARE_FPS / 2 + x_shift;
	else if (e->time.pos == 2)
	{
		e->time.x = WIDTH - SQUARE_FPS / 2 + x_shift;
		e->time.y = HEIGHT - SQUARE_FPS / 2 + y_shift;
	}
	else
	{
		e->time.x = SQUARE_FPS / 2 + x_shift;
		e->time.y = HEIGHT - SQUARE_FPS / 2 + y_shift;
	}
	seg_aff(e, unit);
}

static void	make_fps(t_env *e)
{
	double const begin = e->time.clock_tick / (double)CLOCKS_PER_SEC;
	double const end = (double)clock() / (double)CLOCKS_PER_SEC;

	e->time.count++;
	if (end - begin >= 0.5)
	{
		e->time.fps = ((int)(e->time.count / (end - begin)));
		e->time.clock_tick = (double)clock();
		e->time.count = 0;
	}
}

void		fps(t_env *e)
{
	int			fps;
	int			i;

	fps_corner(e);
	make_fps(e);
	fps = e->time.fps;
	fps = e->time.fps;
	if (fps > 9999)
		fps = 9999;
	i = 0;
	while (fps > 0)
	{
		aff_fps(e, g_digits[fps % 10], i);
		fps /= 10;
		i++;
	}
}
