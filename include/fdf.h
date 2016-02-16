/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 19:06:40 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/16 17:05:59 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <time.h>
# include <math.h>

# define ERROR ft_error(__FILE__, __FUNCTION__, __LINE__)
# define ERRORNO ft_errorno(__FILE__, __FUNCTION__, __LINE__)

# define ESC 53
# define SPACE 49

# define UP 126
# define RIGHT 124
# define LEFT 123
# define DOWN 125

# define KP_PLUS 69
# define KP_MINUS 78
# define KP_0 82
# define KP_1 83
# define KP_5 87
# define KP_6 88
# define KP_8 91
# define KP_9 92

# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25

# define WIDTH 1280
# define HEIGHT 720

# define SQUARE_FPS 100
# define BORDER_FPS 5

# define X1 (e->coord.x1)
# define X2 (e->coord.x2)
# define Y1 (e->coord.y1)
# define Y2 (e->coord.y2)
# define X_T (e->time.x)
# define Y_T (e->time.y)

# define ALERT MAKE_COLOR(2555, 0, 0)
# define RED MAKE_COLOR(154, 80, 79)
# define RED_ORANGE MAKE_COLOR(250, 128, 114)
# define ORANGE MAKE_COLOR(255, 165, 0)
# define YELLOW_ORANGE MAKE_COLOR(236, 177, 70)
# define YELLOW MAKE_COLOR(246, 225, 134)
# define YELLOW_GREEN MAKE_COLOR(160, 219, 142)
# define GREEN MAKE_COLOR(123, 180, 137)
# define BLUE_GREEN MAKE_COLOR(102, 205, 170)
# define BLUE MAKE_COLOR(44, 117, 255)
# define BLUE_PURPLE MAKE_COLOR(49, 92, 107)
# define BLACK MAKE_COLOR(0, 0, 0)

# define MAKE_COLOR(R,G,B) ((uint8_t)(R) <<16 | (uint8_t)(G) <<8 | (uint8_t)(B))
# define TIME_INIT ((t_time){(double)clock(), 0, 0, 2, 0, 0})
# define COORD_INIT ((t_coord){0, 0, 0, 0, RED})

typedef struct		s_coord
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	size_t			color;
}					t_coord;

typedef struct		s_fb
{
	void			*framebuffer;
	int				endian;
	int				l_size;
	int				bpp;
}					t_fb;

typedef struct		s_map
{
	t_ftv			v;
	size_t			l_size;
	size_t			l_nbr;
}					t_map;

/*
** Pos
** 0 - Top left
** 1 - Top right
** 2 - Bottom right
** 3 - Bottom left
*/

typedef struct		s_time
{
	clock_t			clock_tick;
	unsigned int	count;
	int				fps;
	int				pos;
	int				x;
	int				y;
}					t_time;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				in;
	int				deep;
	int				shift_h;
	int				shift_w;
	int				pixel;
	int				mod;
	t_coord			coord;
	t_map			map;
	t_fb			fb;
	t_time			time;
}					t_env;

/*
**Name: Error
**File: ft_error.c
**Desc: error events
*/

int					error(char const *file, char const *function, int line);
int					errorno(char const *file, char const *function, int line);

/*
**Name: Hook
**File: hook.c
**Desc: hook events
*/

int					loop_hook(t_env *e);
int					key_hook(int in, t_env *e);
int					expose_hook(t_env *e);

/*
**Name: Draw
**File: draw.c draw_pixel.c
**Desc: Draw functions
*/

void				black_img(t_env *e, int width, int height);
int					draw_map(t_env *e);
void				draw_line(t_env *e);
void				draw_pixel(t_env *e, int color, int index);

/*
**Name: Parsing
**File: parsing.c
**Desc: parsing functions
*/

int					get_map(int fd, t_env *e);

/*
**Name: Calcul
**File: calcul.c
**Desc: calcul functions
*/

int					calcul(t_env *e, int dot1, int dot2);

/*
**Name: Bonus
**File: bonus.c bonus_fps.c bonus_fps_corner.c
**Desc: bonus functions
*/

void				fps_corner(t_env *e);
void				fps(t_env *e);
void				color_pixel_deep(t_env *e, int value);

#endif
