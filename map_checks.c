/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 03:34:27 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/28 17:45:49 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_spawn(t_player *player)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (i < player->mapsize.y)
	{
		j = 0;
		while (j < player->mapsize.x)
		{
			if (player->worldMap[i][j] == 7)
			{
				player->pos.x = i;
				player->pos.y = j;
				player->worldMap[i][j] = 0;
				n += 1;
			}
			j++;
		}
		i++;
	}
	return (n);
}

int	check_col(t_player *player)
{
	int	**map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map = player->worldMap;
	while (i < player->mapsize.x - 1)
	{
		j = 0;
		while (j < player->mapsize.y - 1 && map[j][i] == 3)
			j++;			
		if (map[j][i] != 1)
			return (0);
		j = player->mapsize.y - 1;
		while (j > 0 && map[j][i] == 3)
			j--;
		if (map[j][i] != 1)
			return (0);
		i++;
	}
	return (1);
}

int	check_line(t_player *player)
{
	int	**map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map = player->worldMap;
	while (i < player->mapsize.y)
	{
		j = 0;
		while (j < player->mapsize.x - 1 && map[i][j] == 3)
			j++;			
		if (map[i][j] != 1)
			return (0);
		j = player->mapsize.x - 1;
		while (j > 0 && map[i][j] == 3)
			j--;
		if (map[i][j] != 1)
			return (0);
		i++;
	}
	return (1);
}

void	set_dir(t_player *player, t_params *p)
{
	if (p->dir == 'S')
	{
		player->dir.x = 1.0;
		player->dir.y = 0.0;
		player->plane.x *= -1;
		player->plane.y *= -1;
	}
	else if (p->dir == 'W')
	{
		double oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(1.6) - player->dir.y * sin(1.6);
		player->dir.y = oldDirX * sin(1.6) + player->dir.y * cos(1.6);
		double oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos(1.6) - player->plane.y * sin(1.6);
		player->plane.y = oldPlaneX * sin(1.6) + player->plane.y * cos(1.6);
	}
	else if (p->dir == 'E')
	{
		double oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(-1.6) - player->dir.y * sin(-1.6);
		player->dir.y = oldDirX * sin(-1.6) + player->dir.y * cos(-1.6);
		double oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos(-1.6) - player->plane.y * sin(-1.6);
		player->plane.y = oldPlaneX * sin(-1.6) + player->plane.y * cos(-1.6);
	}
}