/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:00 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/17 18:27:28 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/*
** TODO: Check returns from mlx
** Keypress : 2 , 0
** Keyrelease : 3 , 1
*/

static int	new_map(char *map)
{
	char	*new_map;
	char	*buff;
	int		fd;

	buff = ft_strjoin("samples/", map);
	new_map = ft_strjoin(buff, ".fdf");
	free(buff);
	fd = open(new_map, O_RDONLY);
	free(new_map);
	if (fd <= 0)
		fd = open(map, O_RDONLY);
	if (fd <= 0)
	{
		ft_putendl_fd("Error opening the file.", 2);
		return (0);
	}
	return (fd);
}

static int	init_env(t_env *e, char *win_name)
{
	e->mlx = mlx_init();
	if (e->mlx == NULL)
		return (1);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, win_name);
	if (e->win == NULL)
		return (1);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	if (e->img == NULL)
		return (1);
	e->fb.framebuffer = mlx_get_data_addr(e->img, &(e->fb.bpp),
										&(e->fb.l_size), &(e->fb.endian));
	if (e->fb.framebuffer == NULL)
		return (1);
	e->in = 0;
	e->pixel = WIDTH / e->map.l_size / 3;
	e->deep = 0;
	e->time = TIME_INIT;
	e->shift_h = 0;
	e->shift_w = 0;
	e->deep = 0;
	return (0);
}

static int	fdf(t_env *e, char *win_name)
{
	if (init_env(e, win_name) != 0)
		return (1);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_hook(e->win, 2, 0, key_hook, e);
	mlx_do_key_autorepeaton(e->mlx);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_env	e;

	if (argc == 2)
	{
		if ((fd = new_map(argv[1])) == 0)
			return (0);
		if (get_map(fd, &e) == 1)
		{
			ft_putendl_fd("Error loading the map.", 2);
			return (0);
		}
		if (close(fd) != 0)
		{
			ft_putendl_fd("Error closing the file.", 2);
			return (0);
		}
		if (fdf(&e, argv[1]) == 1)
			ft_putendl_fd("fdf Error.", 2);
	}
	else
		ft_putendl_fd("Enter only one valid map.", 2);
	return (0);
}
