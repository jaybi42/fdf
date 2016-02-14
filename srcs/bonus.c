/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:00:35 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/14 18:05:13 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		color_pixel_deep(t_env *e, int value)
{
	if (value + e->deep <= 3)
		e->coord.color = RED;
	else if (value + e->deep <= 6)
		e->coord.color = RED_ORANGE;
	else if (value + e->deep <= 9)
		e->coord.color = ORANGE;
	else if (value + e->deep <= 12)
		e->coord.color = YELLOW_ORANGE;
	else if (value + e->deep <= 15)
		e->coord.color = YELLOW;
	else if (value + e->deep <= 18)
		e->coord.color = YELLOW_GREEN;
	else if (value + e->deep < 21)
		e->coord.color = GREEN;
	else if (value + e->deep <= 24)
		e->coord.color = BLUE_GREEN;
	else if (value + e->deep <= 27)
		e->coord.color = BLUE;
	else
		e->coord.color = BLUE_PURPLE;
}
