/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:20:06 by qlentz            #+#    #+#             */
/*   Updated: 2023/04/02 23:02:46 by qlentz           ###   ########.fr       */
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
