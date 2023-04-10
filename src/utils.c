/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:43:47 by qlentz            #+#    #+#             */
/*   Updated: 2023/04/10 12:57:27 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	reset(int sky, int floor, t_img *img)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREENW)
	{
		y = -1;
		while (++y < SCREENH / 2)
			pixel_put(img, x, y, sky);
		while (++y < SCREENH)
			pixel_put(img, x, y, floor);
	}
}

int	hook_cross(void *s)
{
	(void)s;
	exit(0);
	return (0);
}
