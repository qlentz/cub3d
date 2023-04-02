/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:22:45 by qlentz            #+#    #+#             */
/*   Updated: 2023/04/02 23:26:20 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	arr_digit(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]) && arr[i][j] != '\n' && arr[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_colors(t_params *p)
{
	char	**arr;
	int		i;

	arr = ft_split(p->pa[find_tex("F", p)][1], ',');
	i = 1;
	if (arr)
	{
		if (!bind_colors(p, arr, 0))
			i = 0;
		ft_free_tab(arr);
	}
	else
		i = 0;
	arr = ft_split(p->pa[find_tex("C", p)][1], ',');
	if (arr)
	{
		if (!bind_colors(p, arr, 1))
			i = 0;
		ft_free_tab(arr);
	}
	else
		i = 0;
	return (i);
}

int	bind_colors(t_params *p, char **arr, int a)
{
	int	n;

	if (!arr_digit(arr))
		return (0);
	n = ft_atoi(arr[0]);
	if (n <= 255 && n >= 0)
		p->colors[a].r = n;
	else
		return (0);
	n = ft_atoi(arr[1]);
	if (n <= 255 && n >= 0)
		p->colors[a].g = n;
	else
		return (0);
	n = ft_atoi(arr[2]);
	if (n <= 255 && n >= 0)
		p->colors[a].b = n;
	else
		return (0);
	return (1);
}

void	set_params(t_player *pl, t_params *p)
{
	pl->ceiling = encode_rgb(p->colors[1].r, p->colors[1].g, p->colors[1].b);
	pl->floor = encode_rgb(p->colors[0].r, p->colors[0].g, p->colors[0].b);
	pl->tex[0].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx,
			p->pa[find_tex("SO", p)][1], &pl->tex[0].width, &pl->tex[0].height);
	pl->tex[0].addr = mlx_get_img_addr(pl->tex[0].img_ptr,
			&pl->tex[0].bpp, &pl->tex[0].line_len, &pl->tex[0].endian);
	pl->tex[1].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx,
			p->pa[find_tex("WE", p)][1], &pl->tex[1].width, &pl->tex[1].height);
	pl->tex[1].addr = mlx_get_img_addr(pl->tex[1].img_ptr,
			&pl->tex[1].bpp, &pl->tex[1].line_len, &pl->tex[1].endian);
	pl->tex[2].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx,
			p->pa[find_tex("NO", p)][1], &pl->tex[2].width, &pl->tex[2].height);
	pl->tex[2].addr = mlx_get_img_addr(pl->tex[2].img_ptr,
			&pl->tex[2].bpp, &pl->tex[2].line_len, &pl->tex[2].endian);
	pl->tex[3].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx,
			p->pa[find_tex("EA", p)][1], &pl->tex[3].width, &pl->tex[3].height);
	pl->tex[3].addr = mlx_get_img_addr(pl->tex[3].img_ptr,
			&pl->tex[3].bpp, &pl->tex[3].line_len, &pl->tex[3].endian);
}

int	find_tex(char *t, t_params *p)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(t, p->pa[i][0]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
