/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:15:43 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/30 02:27:59 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tex_map(t_params *p)
{
	char		*tab[6];
	t_ivector	i;

	i.x = -1;
	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "EA";
	tab[3] = "WE";
	tab[4] = "F";
	tab[5] = "C";
	while (++i.x < 6 && p->pa[i.x])
	{
		i.y = -1;
		while (++i.y < 6)
		{
			if (p->pa[i.x][0] && ft_strcmp(p->pa[i.x][0], tab[i.y]) == 0)
			{
				tab[i.y] = ".";
				i.y = 10;
			}
		}
		if (i.y < 10)
			return (0);
	}
	return (1);
}

t_params	*init_params(void)
{
	int			i;
	t_params	*p;

	i = 0;
	p = (t_params *)malloc(sizeof(t_params));
	while (i < 6)
	{
		p->pa[i] = NULL;
		i++;
	}
	return (p);
}

int	free_param(t_params *p)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < 6)
	{
		if (p->pa[i])
			ft_free_tab(p->pa[i]);
		i++;
	}
	while (p->lst)
	{
		free(p->lst->content);
		tmp = p->lst;
		p->lst = p->lst->next;
		free(tmp);
	}
	free(p);
	return (0);
}

int	read_params(int fd, t_params *p)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		if (line[0] != '\n')
			p->pa[i++] = ft_split(line, ' ');
		free(line);
	}
	if (!tex_map(p))
		return (free_param(p));
	return (1);
}
