/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:08:48 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/28 18:15:08 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(int i)
{
	int	color;

	if (i == 1)
		color = encode_rgb(255, 0, 0);
	else if (i == 2)
		color = encode_rgb(0, 255, 0);
	else if (i == 3)
		color = encode_rgb(0, 0, 255);
	else if (i == 4)
		color = encode_rgb(120, 120, 0);
	else
		color = encode_rgb(255, 255, 255);
	return (color);
}

t_ray	ray_init(int x, t_player *player)
{
	t_ray	ray;

	ray.camerax = 2 * x / (double)SCREENW - 1;
	ray.rayDir.x = player->dir.x + player->plane.x * ray.camerax;
	ray.rayDir.y = player->dir.y + player->plane.y * ray.camerax;
	ray.map.x = (int)player->pos.x;
	ray.map.y = (int)player->pos.y;
	ray.hit = 0;
	if (ray.rayDir.x == 0)
		ray.deltaDist.x = 1e30;
	else
		ray.deltaDist.x = fabs(1 / ray.rayDir.x);
	if (ray.rayDir.y == 0)
		ray.deltaDist.y = 1e30;
	else
		ray.deltaDist.y = fabs(1 / ray.rayDir.y);
	return (ray);
}

void	step(t_ray *ray, t_player *player)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (player->pos.x - ray->map.x) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->map.x + 1.0 - player->pos.x) * ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (player->pos.y - ray->map.y) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->map.y + 1.0 - player->pos.y) * ray->deltaDist.y;
	}
}

void	dda(t_ray *ray, t_player *player)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (player->worldMap[ray->map.x][ray->map.y] > 0)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDist.x - ray->deltaDist.x);
	else
		ray->perpWallDist = (ray->sideDist.y - ray->deltaDist.y);
}

void	raycast(t_player *player)
{
	int		x;
	t_ray	ray;
	int		line_height;
	int		offset;

	x = 0;
	while (x < SCREENW)
	{
		offset = 0;
		ray = ray_init(x, player);
		step(&ray, player);
		dda(&ray, player);
		line_height = (int)(SCREENH / ray.perpWallDist);
		ray.draw.x = -1 * line_height / 2 + SCREENH / 2;
		if (ray.draw.x < 0)
			ray.draw.x = 0;
		ray.draw.y = line_height / 2 + SCREENH / 2;
		if (ray.draw.y >= SCREENH)
			ray.draw.y = SCREENH - 1;
		draw_wall(player, &ray, x, line_height);
		x++;
	}
}
