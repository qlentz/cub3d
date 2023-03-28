/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:22:45 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/28 22:57:48 by qlentz           ###   ########.fr       */
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

	arr = ft_split(p->paramsarr[find_tex("F", p)][1], ',');
	i = 1;
	if (arr)
	{
		if (!bind_colors(p, arr, 0))
			i = 0;
		ft_free_tab(arr);
	}
	else
		i = 0;
	arr = ft_split(p->paramsarr[find_tex("C", p)][1], ',');
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

void	set_params(t_player *pl, t_texes *t, t_params *p)
{
	t->f.r = p->colors[0].r;
	t->f.g = p->colors[0].g;
	t->f.b = p->colors[0].b;
	t->c.r = p->colors[1].r;
	t->c.g = p->colors[1].g;
	t->c.b = p->colors[1].b;
	remove_nl(p->paramsarr[find_tex("SO", p)][1]);
	remove_nl(p->paramsarr[find_tex("NO", p)][1]);
	remove_nl(p->paramsarr[find_tex("EA", p)][1]);
	remove_nl(p->paramsarr[find_tex("WE", p)][1]);
	pl->texture[0].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx, p->paramsarr[find_tex("SO", p)][1], &pl->texture[0].width, &pl->texture[0].height);
    pl->texture[0].addr = mlx_get_img_addr(pl->texture[0].img_ptr, &pl->texture[0].bpp, &pl->texture[0].line_len, &pl->texture[0].endian);
    pl->texture[1].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx, p->paramsarr[find_tex("WE", p)][1], &pl->texture[1].width, &pl->texture[1].height);
    pl->texture[1].addr = mlx_get_img_addr(pl->texture[1].img_ptr, &pl->texture[1].bpp, &pl->texture[1].line_len, &pl->texture[1].endian);
	pl->texture[2].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx, p->paramsarr[find_tex("NO", p)][1], &pl->texture[2].width, &pl->texture[2].height);
    pl->texture[2].addr = mlx_get_img_addr(pl->texture[2].img_ptr, &pl->texture[2].bpp, &pl->texture[2].line_len, &pl->texture[2].endian);
	pl->texture[3].img_ptr = mlx_xpm_file_to_image(pl->mlx->mlx, p->paramsarr[find_tex("EA", p)][1], &pl->texture[3].width, &pl->texture[3].height);
    pl->texture[3].addr = mlx_get_img_addr(pl->texture[3].img_ptr, &pl->texture[3].bpp, &pl->texture[3].line_len, &pl->texture[3].endian);
}

int	find_tex(char *t, t_params *p)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(t, p->paramsarr[i][0]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
