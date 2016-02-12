/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:54:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/12 18:55:10 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void seg_aff(t_env *e, int unit)
{
	if ((unit & 1) == 1)
	{
		X1 = e->time.x + 8;
		Y1 = e->time.y + 8;
		X2 = e->time.x + 8;
		Y2 = e->time.y + 16;
		draw_line(e);
	}
	if (((unit >> 1) & 1) == 1)
	{
		X1 = e->time.x + 8;
		Y1 = e->time.y;
		X2 = e->time.x + 8;
		Y2 = e->time.y + 8;
		draw_line(e);
	}
	if (((unit >> 2) & 1) == 1)
	{
		X1 = e->time.x;
		Y1 = e->time.y + 16;
		X2 = e->time.x + 8;
		Y2 = e->time.y + 16;
		draw_line(e);
	}
	if (((unit >> 3) & 1) == 1)
	{
		X1 = e->time.x;
		Y1 = e->time.y + 8;
		X2 = e->time.x + 8;
		Y2 = e->time.y + 8;
		draw_line(e);
	}
	if (((unit >> 4) & 1) == 1)
	{
		X1 = e->time.x;
		Y1 = e->time.y;
		X2 = e->time.x + 8;
		Y2 = e->time.y;
		draw_line(e);
	}
	if (((unit >> 5) & 1) == 1)
	{
		X1 = e->time.x;
		Y1 = e->time.y + 8;
		X2 = e->time.x;
		Y2 = e->time.y + 16;
		draw_line(e);
	}
	if (((unit >> 6) & 1) == 1)
	{
		X1 = e->time.x;
		Y1 = e->time.y;
		X2 = e->time.x;
		Y2 = e->time.y + 8;
		draw_line(e);
	}
	return ;
}

void    aff_fps(t_env *e, int unit, int shift)
{
    int x_shift;
    int y_shift;

    x_shift = 30 - shift * 12;
    y_shift = -8;
    if (e->time.pos == 0)
    {
        e->time.x = SQUARE_FPS / 2 + x_shift;
        e->time.y = SQUARE_FPS / 2 + y_shift;
    }
    else if (e->time.pos == 1)
    {
        e->time.x = WIDTH - SQUARE_FPS / 2 + x_shift;
        e->time.y = SQUARE_FPS / 2 + y_shift;
    }
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

static void make_fps(t_env *e)
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



void        fps(t_env *e)
{
	int const	tab[10] = {C_0, C_1, C_2, C_3, C_4, C_5, C_6, C_7, C_8, C_9};
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
		aff_fps(e, tab[fps % 10], i);
		fps /= 10;
        i++;
	}
}
