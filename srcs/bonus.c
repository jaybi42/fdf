/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:00:35 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/12 16:07:03 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		color_pixel_deep(t_env *e, int value)
{
	if (value <= 32)
		e->coord.color = RED;
	else if (value <= 64)
		e->coord.color = RED_ORANGE;
	else if (value <= 96)
		e->coord.color = ORANGE;
	else if (value <= 128)
		e->coord.color = YELLOW_ORANGE;
	else if (value <= 150)
		e->coord.color = YELLOW;
	else if (value <= 182)
		e->coord.color = YELLOW_GREEN;
	else if (value < 214)
		e->coord.color = GREEN;
	else if (value <= 246)
		e->coord.color = BLUE_GREEN;
	else if (value <= 278)
		e->coord.color = BLUE;
	else
		e->coord.color = BLUE_PURPLE;
}
