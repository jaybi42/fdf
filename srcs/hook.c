/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 19:48:09 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/15 15:58:12 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static int	key_hook_exp(int in, t_env *e)
{
	if (in == KP_PLUS)
		e->pixel++;
	else if (in == KP_MINUS && e->pixel > 0)
		e->pixel--;
	else if (in == KP_0)
		e->deep--;
	else if (in == KP_1 && e->deep < 100)
		e->deep++;
	else if (in == UP)
		e->shift_h -= 10;
	else if (in == DOWN)
		e->shift_h += 10;
	else if (in == LEFT)
		e->shift_w -= 10;
	else if (in == RIGHT)
		e->shift_w += 10;
	else if (in == KEY_1 || in == KEY_2 || in == KEY_3 || in == KEY_4)
		e->mod = in;
	return (0);
}

int			key_hook(int in, t_env *e)
{
	e->in = in;
	if (in == ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	if (in == KP_5)
		e->time.pos = 3;
	if (in == KP_6)
		e->time.pos = 2;
	if (in == KP_8)
		e->time.pos = 0;
	if (in == KP_9)
		e->time.pos = 1;
	key_hook_exp(in, e);
	return (0);
}

int			expose_hook(t_env *e)
{
	if (draw_map(e))
	{
		ERROR;
		exit(0);
	}
	return (0);
}

int			loop_hook(t_env *e)
{
	if (draw_map(e))
	{
		ERROR;
		exit(0);
	}
	return (0);
}
