/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:14:59 by mpouce            #+#    #+#             */
/*   Updated: 2023/03/28 21:14:55 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_texture *texture, int x, int y)
{
	if (x >= 0 && y >= 0)
	{
		return (*(int *)(texture->addr + (4 * texture->width * y) + (4 * x)));
	}
	return (0x0);
}

void	draw_wall_line(t_player *player, t_ray *ray, int x, t_textpixel *tex)
{
	double	tex_step;
	double	tex_pos;
	int		lh;
	int		i;
	int		color;

	lh = (int)(SCREENH / ray->perpWallDist);
	i = ray->draw.x;
	tex_step = 1.0 * player->texture[ray->side + tex->offset].height / lh;
	tex_pos = (ray->draw.x - SCREENH / 2 + lh / 2) * tex_step;
	while (i < ray->draw.y)
	{
		tex->tex.y = (int)tex_pos
			& (player->texture[ray->side + tex->offset].height - 1);
		tex_pos += tex_step;
		color = get_pixel_color(&player->texture[ray->side + tex->offset],
				tex->tex.x, tex->tex.y);
		pixel_put(player->mlx->img, x, i, color);
		i++;
	}
}

void	draw_wall(t_player *player, t_ray *ray, int x, int line_height)
{
	t_textpixel	tex;
	double		wall_x;
	int			i;

	tex.offset = 0;
	if (ray->side == 0)
		wall_x = player->pos.y + ray->perpWallDist * ray->rayDir.y;
	else
		wall_x = player->pos.x + ray->perpWallDist * ray->rayDir.x;
	wall_x -= floor(wall_x);
	if ((ray->side == 0 && ray->rayDir.x < 0)
		|| (ray->side == 1 && ray->rayDir.y > 0))
		tex.offset = 2;
	tex.tex.x = (int)(wall_x * player->texture[ray->side + tex.offset].width);
	tex.tex.x = player->texture[ray->side + tex.offset].width - tex.tex.x - 1;
	draw_wall_line(player, ray, x, &tex);
}
