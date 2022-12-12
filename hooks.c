/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:19:27 by qlentz            #+#    #+#             */
/*   Updated: 2022/12/12 16:04:23 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_keydown(int key, t_player *player)
{
	if (key == K_ESC)
		close_win(player->mlx);
	else if (key == K_UP)
	{
		if((int)player->worldMap[(int)(player->pos.x + player->dir.x)][(int)player->pos.y] == 0)
			player->pos.x += player->dir.x * 0.25;
		if((int)player->worldMap[(int)player->pos.x][(int)(player->pos.y + player->dir.y)] == 0)
			player->pos.y += player->dir.y * 0.25;
	}
	else if (key == K_DOWN)
	{
		if((int)player->worldMap[(int)(player->pos.x - player->dir.x)][(int)player->pos.y] == 0)
			player->pos.x -= player->dir.x * 0.25;
		if((int)player->worldMap[(int)player->pos.x][(int)(player->pos.y - player->dir.y)] == 0)
			player->pos.y -= player->dir.y * 0.25;
	}
	else if (key == K_LEFT)
	{
		double oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(0.1) - player->dir.y * sin(0.1);
		player->dir.y = oldDirX * sin(0.1) + player->dir.y * cos(0.1);
		double oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos(0.1) - player->plane.y * sin(0.1);
		player->plane.y = oldPlaneX * sin(0.1) + player->plane.y * cos(0.1);
	}
	else if (key == K_RIGHT)
	{
		double oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(-0.1) - player->dir.y * sin(-0.1);
		player->dir.y = oldDirX * sin(-0.1) + player->dir.y * cos(-0.1);
		double oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos(-0.1) - player->plane.y * sin(-0.1);
		player->plane.y = oldPlaneX * sin(-0.1) + player->plane.y * cos(-0.1);
	}
	reset(encode_rgb(121, 210, 227), encode_rgb(0, 0, 0), player->mlx->img);
	raycast(player);
	mlx_put_image_to_window(player->mlx->mlx, player->mlx->win, player->mlx->img->img, 0, 0);
	return (0);
}