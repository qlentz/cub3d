/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:15:43 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/26 22:38:57 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int tex_map(t_params *p)
{
	char	*tab[6];
	int		i;
	int		j;

	j = 0;
	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "EA";
	tab[3] = "WE";
	tab[4] = "F";
	tab[5] = "C";

	while (p->paramsarr[j])
	{
		i = 0;
		while (i < 6)
		{
			if (ft_strcmp(p->paramsarr[j][0], tab[i]) == 0)
			{
				tab[i] = ".";
				i = 10;
			}
			i++;
		}
		if (i < 10)
			return (0);
		j++;
	}
	return (1);
	
}

t_params *init_params(void)
{
	int			i;
	t_params	*p;

	i = 0;
	p = (t_params *)malloc(sizeof(t_params));
	while (i < 6)
	{
		p->paramsarr[i] = NULL;
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
		if (p->paramsarr[i])
			ft_free_tab(p->paramsarr[i]);
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
			p->paramsarr[i++] = ft_split(line, ' ');
		free(line);
	}
	if (!tex_map(p))
		return(free_param(p));
	return(1);
}