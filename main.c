/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:12:56 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/28 18:13:10 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_array(int **array)
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
	player.texture[0].img_ptr = mlx_xpm_file_to_image(player.mlx->mlx, "textures/wall.xpm", &player.texture[0].width, &player.texture[0].height);
    player.texture[0].addr = mlx_get_img_addr(player.texture[0].img_ptr, &player.texture[0].bpp, &player.texture[0].line_len, &player.texture[0].endian);
    player.texture[1].img_ptr = mlx_xpm_file_to_image(player.mlx->mlx, "textures/eagle.xpm", &player.texture[1].width, &player.texture[1].height);
    player.texture[1].addr = mlx_get_img_addr(player.texture[1].img_ptr, &player.texture[1].bpp, &player.texture[1].line_len, &player.texture[1].endian);
    player.texture[2].img_ptr = mlx_xpm_file_to_image(player.mlx->mlx, "textures/wall_2.xpm", &player.texture[2].width, &player.texture[2].height);
    player.texture[2].addr = mlx_get_img_addr(player.texture[2].img_ptr, &player.texture[2].bpp, &player.texture[2].line_len, &player.texture[2].endian);
    player.texture[3].img_ptr = mlx_xpm_file_to_image(player.mlx->mlx, "textures/side_2.xpm", &player.texture[3].width, &player.texture[3].height);
    player.texture[3].addr = mlx_get_img_addr(player.texture[3].img_ptr, &player.texture[3].bpp, &player.texture[3].line_len, &player.texture[3].endian);
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
