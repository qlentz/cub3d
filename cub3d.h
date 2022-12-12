/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:07:57 by qlentz            #+#    #+#             */
/*   Updated: 2022/12/11 18:58:21 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SCREENW	1000
# define SCREENH	800
# define MAPW 		24
# define MAPH 		24
# define K_ESC 		53
# define K_UP		126
# define K_DOWN		125
# define K_LEFT		123
# define K_RIGHT	124
# include "mlx.h"
# include "math.h"
# include "stdio.h"
# include "stdlib.h"

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	t_img		*img;
}				t_mlx;

typedef struct s_vector {
	double	x;
	double	y;
}				t_vector;

typedef struct s_player {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		movespeed;
	double		rotspeed;
	int			**worldMap;
	t_mlx		*mlx;
}				t_player;

void	pixel_put(t_img *data, int x, int y, int color);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	close_win(t_mlx *mlx);
void	verLine(t_mlx *mlx, int x, int start, int end, int color);
void	reset(int sky, int floor, t_img *img);
void	raycast(t_player *player);
int		hook_keydown(int key, t_player *player);
#endif