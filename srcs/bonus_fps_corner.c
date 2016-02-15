/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fps_corner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 16:01:49 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/15 16:03:55 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	border_0(t_env *e)
{
	int i;

	i = -1;
	X1 = 0;
	Y1 = 0;
	black_img(e, SQUARE_FPS, SQUARE_FPS);
	Y1 = SQUARE_FPS;
	X2 = SQUARE_FPS;
	Y2 = SQUARE_FPS;
	while (++i < BORDER_FPS)
	{
		draw_line(e);
		Y1--;
		Y2--;
	}
	i = -1;
	X1 = SQUARE_FPS;
	Y1 = 0;
	Y2 = SQUARE_FPS;
	while (++i < BORDER_FPS)
	{
		draw_line(e);
		X1--;
		X2--;
	}
}

static void	border_1(t_env *e)
{
	int i;

	i = -1;
	X1 = WIDTH - SQUARE_FPS;
	Y1 = 0;
	black_img(e, SQUARE_FPS, SQUARE_FPS);
	Y1 = SQUARE_FPS;
	X2 = WIDTH;
	Y2 = SQUARE_FPS;
	while (++i < BORDER_FPS)
	{
		draw_line(e);
		Y1--;
		Y2--;
	}
	i = -1;
	Y1 = 0;
	X2 = WIDTH - SQUARE_FPS;
	Y2 = SQUARE_FPS;
	while (++i < BORDER_FPS)
	{
		draw_line(e);
		X1++;
		X2++;
	}
}

static void	border_2(t_env *e)
{
	int i;

	i = 0;
	X1 = WIDTH - SQUARE_FPS;
	Y1 = HEIGHT - SQUARE_FPS;
	black_img(e, SQUARE_FPS, SQUARE_FPS);
	X2 = WIDTH;
	Y2 = HEIGHT - SQUARE_FPS;
	while (i < BORDER_FPS)
	{
		draw_line(e);
		Y1++;
		Y2++;
		i++;
	}
	i = -1;
	Y1 = HEIGHT - SQUARE_FPS;
	X2 = WIDTH - SQUARE_FPS;
	Y2 = HEIGHT;
	while (++i < BORDER_FPS)
	{
		draw_line(e);
		X1++;
		X2++;
	}
}

static void	border_3(t_env *e)
{
	int i;

	i = 0;
	X1 = 0;
	Y1 = HEIGHT - SQUARE_FPS;
	black_img(e, SQUARE_FPS, SQUARE_FPS);
	X2 = SQUARE_FPS;
	Y2 = HEIGHT - SQUARE_FPS;
	while (i < BORDER_FPS)
	{
		draw_line(e);
		Y1++;
		Y2++;
		i++;
	}
	i = -1;
	X1 = SQUARE_FPS;
	Y1 = HEIGHT - SQUARE_FPS;
	Y2 = HEIGHT;
	while (++i < BORDER_FPS)
	{
		draw_line(e);
		X1--;
		X2--;
	}
}

void		fps_corner(t_env *e)
{
	if (e->time.fps < 25)
		e->coord.color = ALERT;
	else if (e->time.fps < 60)
		e->coord.color = YELLOW;
	else
		e->coord.color = GREEN;
	if (e->time.pos == 0)
		border_0(e);
	else if (e->time.pos == 1)
		border_1(e);
	else if (e->time.pos == 2)
		border_2(e);
	else
		border_3(e);
}
