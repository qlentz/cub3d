/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:08:48 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/31 23:44:53 by qlentz           ###   ########.fr       */
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
	ray.raydir.x = player->dir.x + player->plane.x * ray.camerax;
	ray.raydir.y = player->dir.y + player->plane.y * ray.camerax;
	ray.map.x = (int)player->pos.x;
	ray.map.y = (int)player->pos.y;
	ray.hit = 0;
	if (ray.raydir.x == 0)
		ray.deltadist.x = 1e30;
	else
		ray.deltadist.x = fabs(1 / ray.raydir.x);
	if (ray.raydir.y == 0)
		ray.deltadist.y = 1e30;
	else
		ray.deltadist.y = fabs(1 / ray.raydir.y);
	return (ray);
}

void	step(t_ray *ray, t_player *player)
{
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (player->pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - player->pos.x) * ray->deltadist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (player->pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - player->pos.y) * ray->deltadist.y;
	}
}

void	dda(t_ray *ray, t_player *player)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (player->worldmap[ray->map.x][ray->map.y] > 0)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedist.x - ray->deltadist.x);
	else
		ray->perpwalldist = (ray->sidedist.y - ray->deltadist.y);
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
		line_height = (int)(SCREENH / ray.perpwalldist);
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
