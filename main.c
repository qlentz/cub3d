/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:12:56 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/29 15:21:40 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(int **array)
{
	for (int i = 0; i < 24; i++)
	{
		free(array[i]);
	}
	free(array);
}

int	main(void)
{
	t_player player;
	player.pos.x = 0.0;
	player.pos.y = 0.0;
	player.dir.x = -1.0;
	player.dir.y = 0.0;
	player.plane.x = 0.0;
	player.plane.y = 0.66;
	t_mlx		mlx;
	t_img		img;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREENW, SCREENH, "cub3d");
	img.img = mlx_new_image(mlx.mlx, SCREENW, SCREENH);
	img.addr = mlx_get_img_addr(img.img, &img.bpp,
			&img.line_length, &img.endian);
	mlx.img = &img;
	player.mlx = &mlx;
	if (!parser("bite.cub", &player))
	{
		ft_putendl_fd("error !", 2);
		return (1);
	}
	reset(encode_rgb(121, 210, 227), encode_rgb(0, 0, 0), mlx.img);
	raycast(&player);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
	mlx_hook(mlx.win, 2, (1L<<0), hook_keydown, &player);
	mlx_loop(mlx.mlx);
	return (0);
}
