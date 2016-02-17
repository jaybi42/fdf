/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 17:11:03 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/17 16:31:27 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	split_line(char const *line, t_env *e)
{
	int i;
	int nbr;

	i = 0;
	e->map.l_size = 0;
	while (*line != '\0')
	{
		if (*line == '-' && (ft_isdigit(*(line + 1)) == 1))
			line++;
		if (ft_isdigit(*line))
		{
			nbr = ft_atoi(line++);
			if (ftv_pushback(&(e->map.v), &nbr) == 1)
				return (1);
			e->map.l_size++;
			while (ft_isdigit(*line))
				line++;
		}
		else if (*line == ' ' || *line == '\t')
			line++;
		else
			return (1);
	}
	e->map.l_nbr++;
	return (0);
}

int			get_map(int fd, t_env *e)
{
	char	*line;
	int		ret;

	e->map.v = FTV_INIT(int);
	e->map.l_nbr = 0;
	ret = 1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (split_line(line, e) == 1)
			return (1);
		ft_strdel(&line);
	}
	if (ret == -1)
		return (1);
	return (0);
}
