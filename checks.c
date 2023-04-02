/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:20:06 by qlentz            #+#    #+#             */
/*   Updated: 2023/04/02 23:26:56 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_cub(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] != 'b' || s[len - 2] != 'u'
		|| s[len - 3] != 'c' || s[len - 4] != '.')
		return (0);
	return (1);
}

int	extra_map_check(t_player *p)
{
	int	h;
	int	w;

	h = 1;
	w = 1;
	while (h < p->mapsize.y - 1)
	{
		w = 1;
		while (w < p->mapsize.x - 1)
		{
			if (p->worldmap[h][w] == 0 && (p->worldmap[h - 1][w] == 3
				|| p->worldmap[h + 1][w] == 3 || p->worldmap[h]
					[w - 1] == 3 || p->worldmap[h][w + 1] == 3))
				return (0);
			w++;
		}
		h++;
	}
	return (1);
}

int	check_tex(t_params *p)
{
	int	fd[4];
	int	i;

	i = 1;
	remove_nl(p);
	fd[0] = open(p->pa[find_tex("SO", p)][1], O_RDONLY);
	fd[1] = open(p->pa[find_tex("NO", p)][1], O_RDONLY);
	fd[2] = open(p->pa[find_tex("EA", p)][1], O_RDONLY);
	fd[3] = open(p->pa[find_tex("WE", p)][1], O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
		i = 0;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (i);
}
