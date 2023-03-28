/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:08:48 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/28 16:25:19 by mpouce           ###   ########.fr       */
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

int get_pixel_color(t_texture *texture, int x, int y)
{
	/*if (x >= texture->width)
		x = x % texture->width;
	if (y >= texture->height)
		y = y % texture->height;*/
	if (x >= 0 && y >= 0)
	{
		return (*(int*)(texture->addr + (4 * texture->width * y) + (4 * x)));
	}
	return (0x0);
}

void	raycast(t_player *player)
{
	int		x;
	t_ray	ray;
	int		line_height;
	int		color;
	int		offset;
	int tex_X;
	int tex_Y;
	double wall_X;
	
	x = 0;
	int last_x = -1;
	while (x < SCREENW)
	{
		offset = 0;
		ray = ray_init(x, player);
		step(&ray, player);
		dda(&ray, player);
		line_height = (int)(SCREENH / ray.perpWallDist);
		printf("ray dir : %f, %f\n", ray.rayDir.x, ray.rayDir.y);
		ray.draw.x = - line_height / 2 + SCREENH / 2;
		if (ray.draw.x < 0)
			ray.draw.x = 0;
		ray.draw.y = line_height / 2 + SCREENH / 2;
		if (ray.draw.y >= SCREENH)
			ray.draw.y = SCREENH - 1;
		if (ray.side == 0)
			wall_X = player->pos.y + ray.perpWallDist * ray.rayDir.y;
		else
			wall_X = player->pos.x + ray.perpWallDist * ray.rayDir.x;
		wall_X -= floor(wall_X);
		tex_X = (int)(wall_X * player->texture[ray.side + offset].width);
		//printf("wall_X is %f, tex_X is %d\n", wall_X, tex_X);
		if (ray.side == 0 && ray.rayDir.x > 0)
			tex_X = player->texture[ray.side + offset].width - tex_X - 1;
		if (ray.side == 0 && ray.rayDir.x < 0)
		{
			offset = 2;
			tex_X = player->texture[ray.side + offset].width - tex_X - 1;
		}
		if (ray.side == 1 && ray.rayDir.y < 0)
			tex_X = player->texture[ray.side + offset].width - tex_X - 1;
		if (ray.side == 1 && ray.rayDir.y > 0)
		{
			offset = 2;
			tex_X = player->texture[ray.side + offset].width - tex_X - 1;
		}
		double tex_step = 1.0 * player->texture[ray.side + offset].height / line_height;
		double tex_pos = (ray.draw.x - SCREENH / 2 + line_height / 2) * tex_step;
		for (int i = ray.draw.x; i < ray.draw.y; i++)
		{
			//printf("tex coord : %d,%d\n", tex_X, tex_Y);
			tex_Y = (int)tex_pos & (player->texture[ray.side + offset].height - 1);
			tex_pos += tex_step;
			color = get_pixel_color(&player->texture[ray.side + offset], tex_X, tex_Y);
			pixel_put(player->mlx->img, x, i, color);
		}
		x++;
	}
}
