/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:19:27 by qlentz            #+#    #+#             */
/*   Updated: 2023/04/01 19:17:48 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_player *p, double value)
{
	double	dirx;
	double	planex;

	dirx = p->dir.x;
	p->dir.x = p->dir.x * cos(value) - p->dir.y * sin(value);
	p->dir.y = dirx * sin(value) + p->dir.y * cos(value);
	planex = p->plane.x;
	p->plane.x = p->plane.x * cos(value) - p->plane.y * sin(value);
	p->plane.y = planex * sin(value) + p->plane.y * cos(value);
}

void	strafe(t_player *p, int val)
{
	if ((int)p->worldmap[(int)(p->pos.x + p->plane.x * 0.25 * val)]
		[(int)p->pos.y] == 0)
		p->pos.x += p->plane.x * 0.25 * val;
	if ((int)p->worldmap[(int)p->pos.x]
		[(int)(p->pos.y + p->plane.y * 0.25 * val)] == 0)
		p->pos.y += p->plane.y * 0.25 * val;
}

void	move_updown(t_player *p, int val)
{
	if ((int)p->worldmap[(int)(p->pos.x + p->dir.x * 0.25 * val)]
		[(int)p->pos.y] == 0)
		p->pos.x += p->dir.x * 0.25 * val;
	if ((int)p->worldmap[(int)p->pos.x]
		[(int)(p->pos.y + p->dir.y * 0.25 * val)] == 0)
		p->pos.y += p->dir.y * 0.25 * val;
}

int	hook_keydown(int key, t_player *p)
{
	if (key == K_ESC)
		close_win(p->mlx);
	else if (key == K_UP || key == K_W)
		move_updown(p, 1);
	else if (key == K_DOWN || key == K_S)
		move_updown(p, -1);
	else if (key == K_LEFT)
		rotate(p, 0.1);
	else if (key == K_RIGHT)
		rotate(p, -0.1);
	else if (key == K_A)
		strafe(p, -1);
	else if (key == K_D)
		strafe(p, 1);
	reset(p->ceiling, p->floor, p->mlx->img);
	raycast(p);
	mlx_put_image_to_window(p->mlx->mlx, p->mlx->win, p->mlx->img->img, 0, 0);
	return (0);
}
