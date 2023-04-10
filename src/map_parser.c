/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:41:44 by qlentz            #+#    #+#             */
/*   Updated: 2023/04/02 22:59:24 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	largest_line(t_params *p)
{
	int		n;
	t_list	*tmp;

	n = 0;
	tmp = p->lst;
	while (tmp)
	{
		if ((int)ft_strlen((char *)tmp->content) > n)
			n = (int)ft_strlen((char *)tmp->content);
		tmp = tmp->next;
	}
	return (n);
}

void	clone_line(int *tab, int size, char *s, t_params *p)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\n')
			tab[i] = 3;
		else if (s[i] == '1')
			tab[i] = 1;
		else if (s[i] == '0')
			tab[i] = 0;
		else if (s[i] == 'S' || s[i] == 'N' || s[i] == 'W' || s[i] == 'E')
		{
			tab[i] = 7;
			p->dir = s[i];
		}
		i++;
	}
	while (i < size)
		tab[i++] = 3;
}

int	map_to_int(t_player *player, t_params *p)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = p->lst;
	player->mapsize.y = ft_lstsize(p->lst);
	player->mapsize.x = largest_line(p);
	player->worldmap = (int **)malloc(sizeof(int *) * player->mapsize.y);
	if (!player->worldmap)
		return (0);
	while (tmp)
	{
		player->worldmap[i] = (int *)malloc(sizeof(int) * player->mapsize.x);
		if (!player->worldmap[i])
			return (0);
		clone_line(player->worldmap[i], player->mapsize.x,
			(char *)tmp->content, p);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

void	print_tab(int **tab, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			ft_printnbr(tab[i][j]);
			j++;
		}
		ft_printchar('\n');
		i++;
	}
}

int	map_parser(t_player *player, t_params *p)
{
	if (!map_to_int(player, p))
		return (0);
	player->worldmap = player->worldmap;
	if (!check_line(player) || !check_col(player) || !extra_map_check(player))
		fatal_error("map not closed");
	if (check_spawn(player) != 1)
		fatal_error("Wrong spawns");
	set_dir(player, p);
	return (1);
}
