/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 15:48:22 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/15 15:20:08 by jguthert         ###   ########.fr       */
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
	e->coord.y1 = dot1 / e->map.l_size * e->pixel - value1;
	e->coord.x1 = dot1 % e->map.l_size * e->pixel - (e->coord.y1 + value1) / 2;
	e->coord.y2 = dot2 / e->map.l_size * e->pixel - value2;
	e->coord.x2 = dot2 % e->map.l_size * e->pixel - (e->coord.y2 + value2) / 2;
}

static void	conique(t_env *e, int dot1, int dot2)
{
	int		value1;
	int		value2;

	value1 = ((int*)e->map.v.data)[dot1];
	value2 = ((int*)e->map.v.data)[dot2];
	value1 == 0 ? value1 : (value1 += e->deep);
	value2 == 0 ? value2 : (value2 += e->deep);
//	printf("AVANT: dot1[%i,%i] dot2[%i,%i]\n", e->coord.x1, e->coord.y1, e->coord.x2, e->coord.y2);
	e->coord.y1 = dot1 / e->map.l_size * e->pixel - value1;
	e->coord.x1 = dot1 % e->map.l_size * e->pixel - (e->coord.y1 + value1) / 2;
	e->coord.y2 = dot2 / e->map.l_size * e->pixel - value2;
	e->coord.x2 = dot2 % e->map.l_size * e->pixel - (e->coord.y2 + value2) / 2;
//	printf("apres: dot1[%i,%i] dot2[%i,%i]\n", e->coord.x1, e->coord.y1, e->coord.x2, e->coord.y2);
}

static void	para(t_env *e, int dot1, int dot2)
{
//	printf("AVANT: dot1[%i,%i] dot2[%i,%i]\n", e->coord.x1, e->coord.y1, e->coord.x2, e->coord.y2);
	e->coord.y1 = dot1 / e->map.l_size * e->pixel;
	e->coord.x1 = dot1 % e->map.l_size * e->pixel - e->coord.y1 / 2;
	e->coord.y2 = dot2 / e->map.l_size * e->pixel;
	e->coord.x2 = dot2 % e->map.l_size * e->pixel - e->coord.y2 / 2;
//	printf("apres: dot1[%i,%i] dot2[%i,%i]\n", e->coord.x1, e->coord.y1, e->coord.x2, e->coord.y2);
}

static void	perso(t_env *e, int dot1, int dot2)
{
	e->coord.x1 = dot1 % e->map.l_size * e->pixel;
	e->coord.y1 = dot1 / e->map.l_size * e->pixel;
	e->coord.x2 = dot2 % e->map.l_size * e->pixel;
	e->coord.y2 = dot2 / e->map.l_size * e->pixel;
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
	return (0);
}
