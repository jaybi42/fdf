/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 15:48:22 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/16 14:22:00 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**e->coord.x1 = dot1 % e->map.l_size * e->pixel;
**e->coord.y1 = dot1 / e->map.l_size * e->pixel;
**e->coord.x2 = dot2 % e->map.l_size * e->pixel;
**e->coord.y2 = dot2 / e->map.l_size * e->pixel;
*/

static void	iso(t_env *e, int dot1, int dot2)
{
	int		value1;
	int		value2;

	value1 = ((int*)e->map.v.data)[dot1];
	value2 = ((int*)e->map.v.data)[dot2];
	color_pixel_deep(e, (value1 > value2 ? value1 : value2));
	value1 == 0 ? value1 : (value1 += e->deep);
	value2 == 0 ? value2 : (value2 += e->deep);
	value1 *= e->pixel;
	value2 *= e->pixel;
	Y1 = dot1 / e->map.l_size * e->pixel - value1;
	X1 = dot1 % e->map.l_size * e->pixel - (Y1 + value1) / 2;
	Y2 = dot2 / e->map.l_size * e->pixel - value2;
	X2 = dot2 % e->map.l_size * e->pixel - (Y2 + value2) / 2;
}

static void	conique(t_env *e, int dot1, int dot2)
{
	int		value1;
	int		value2;

	value1 = ((int*)e->map.v.data)[dot1];
	value2 = ((int*)e->map.v.data)[dot2];
	value1 == 0 ? value1 : (value1 += e->deep);
	value2 == 0 ? value2 : (value2 += e->deep);
	Y1 = dot1 / e->map.l_size * e->pixel - value1;
	X1 = dot1 % e->map.l_size * e->pixel - (Y1 + value1) / 2;
	Y2 = dot2 / e->map.l_size * e->pixel - value2;
	X2 = dot2 % e->map.l_size * e->pixel - (Y2 + value2) / 2;
}

static void	para(t_env *e, int dot1, int dot2)
{
	Y1 = dot1 / e->map.l_size * e->pixel;
	X1 = dot1 % e->map.l_size * e->pixel - Y1 / 2;
	Y2 = dot2 / e->map.l_size * e->pixel;
	X2 = dot2 % e->map.l_size * e->pixel - Y2 / 2;
}

static void	perso(t_env *e, int dot1, int dot2)
{
	X1 = dot1 % e->map.l_size * e->pixel;
	Y1 = dot1 / e->map.l_size * e->pixel;
	X2 = dot2 % e->map.l_size * e->pixel;
	Y2 = dot2 / e->map.l_size * e->pixel;
}

int			calcul(t_env *e, int dot1, int dot2)
{
	if (e->mod == KEY_1)
		iso(e, dot1, dot2);
	else if (e->mod == KEY_2)
		para(e, dot1, dot2);
	else if (e->mod == KEY_3)
		conique(e, dot1, dot2);
	else
		perso(e, dot1, dot2);
	if ((X1 < 0 && X2 < 0) || (X1 > WIDTH && X2 > WIDTH))
		return (0);
	if ((Y1 < 0 && Y2 < 0) || (Y1 > HEIGHT && Y2 > HEIGHT))
		return (0);
	return (0);
}
