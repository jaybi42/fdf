/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 19:17:14 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/11 17:30:50 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		pixel_8(t_env *e, int color, int index)
{
	((uint8_t*)e->fb.framebuffer)[index] = (uint8_t)color;
}

static void		pixel_16(t_env *e, int color, int index)
{
	((uint16_t*)e->fb.framebuffer)[index] = (uint16_t)color;
}

static void		pixel_32(t_env *e, int color, int index)
{
	((uint32_t*)e->fb.framebuffer)[index] = (uint32_t)color;
}

static void		pixel_64(t_env *e, int color, int index)
{
	((uint64_t*)e->fb.framebuffer)[index] = (uint64_t)color;
}

void	draw_pixel(t_env *e, int color, int index)
{
	if (e->fb.bpp == 8)
		pixel_8(e, color, index);
	else if (e->fb.bpp == 16)
		pixel_16(e, color, index);
	else if (e->fb.bpp == 32)
		pixel_32(e, color, index);
	else if (e->fb.bpp == 64)
		pixel_64(e, color, index);
}
