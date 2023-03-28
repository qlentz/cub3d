/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:07:57 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/28 22:36:34 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SCREENW	1000
# define SCREENH	800
# define K_ESC 		53
# define K_UP		126
# define K_W		13
# define K_DOWN		125
# define K_S		1
# define K_LEFT		123
# define K_A		0
# define K_RIGHT	124
# define K_D		2

# include "mlx.h"
# include "math.h"
# include "stdio.h"
# include "stdlib.h"
# include "libft.h"
# include <fcntl.h>

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

typedef struct s_ivector {
	int	x;
	int y;
}				t_ivector;

typedef struct s_textpixel
{
	t_ivector	tex;
	int			offset;
}				t_textpixel;

typedef struct s_texture {
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}				t_texture;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_params {
	char 	**paramsarr[6];
	t_color	colors[2];
	t_list	*lst;
	char	dir;
}				t_params;

typedef struct s_tex {
	void	*tex;
	int		width;
	int		height;
}				t_tex;

typedef struct s_texes {
	t_tex	no;
	t_tex	so;
	t_tex	ea;
	t_tex	we;
	t_color	f;
	t_color	c;
}				t_texes;

typedef struct s_player {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_ivector	mapsize;
	double		movespeed;
	double		rotspeed;
	int			**worldMap;
	t_texes		texes;
	t_mlx		*mlx;
	t_texture	texture[4];
}				t_player;

typedef struct s_ray {
	t_vector	rayDir;
	t_vector	sideDist;
	t_vector	deltaDist;
	t_ivector	map;
	t_vector	step;
	double 		camerax;
	int			hit;
	int			side;
	t_ivector	draw;
	double 		perpWallDist;
}				t_ray;


/* draw_walls.c */
int		get_pixel_color(t_texture *texture, int x, int y);
void	draw_wall_line(t_player *player, t_ray *ray, int x, t_textpixel *tex);
void	draw_wall(t_player *player, t_ray *ray, int x, int line_height);

void	pixel_put(t_img *data, int x, int y, int color);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	close_win(t_mlx *mlx);
void	ver_line(t_mlx *mlx, int x, t_ivector coordinates, int color);
void	reset(int sky, int floor, t_img *img);
void	raycast(t_player *player);
int		hook_keydown(int key, t_player *player);
int get_pixel_color(t_texture *texture, int x, int y);

int			tex_map(t_params *p);
int			param_parser(char *file, t_player *player, t_params *p);
int			parse_colors(t_params *p);
int			read_params(int fd, t_params *p);
int			find_tex(char *t, t_params *p);
int			free_param(t_params *p);
t_params	*init_params(void);
int			bind_colors(t_params *p, char **arr, int a);
int			arr_digit(char **arr);
int			check_char_map(t_player *player, t_params *p, int fd);
int			string_map_check(char *s);
void		set_params(t_player *pl, t_texes *t, t_params *p);
int			map_parser(t_player *player, t_params *p);
int			check_spawn(t_player *player);
int			check_col(t_player *player);
int			check_line(t_player *player);
void		set_dir(t_player *player, t_params *p);
void		remove_nl(char *str);
int			parser(char *file, t_player *player);

#endif
