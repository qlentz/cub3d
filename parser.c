/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 23:14:18 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/29 15:16:02 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

int	parser(char *file, t_player *player)
{
	t_params	*p;

	p = init_params();
	if (!param_parser(file, player, p))
		return (0);
	if (!map_parser(player, p))
		return (0);
	free_param(p);
	return (1);
}

int	param_parser(char *file, t_player *player, t_params *p)
{
	int			fd;
	int			size;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!read_params(fd, p))
		return (0);
	if (!parse_colors(p))
		return (0);
	set_params(player, &player->texes, p);
	size = check_char_map(p, fd);
	close(fd);
	return (size);
}

int	check_char_map(t_params *p, int fd)
{
	char	*line;
	int		n;

	n = 0;
	line = p->pa[0][1];
	p->lst = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!string_map_check(line))
		{
			free(line);
			return (0);
		}
		if (line[0] != '\n')
		{
			ft_lstadd_back(&p->lst, ft_lstnew((void *)line));
			n++;
		}
		else
			free(line);
	}
	return (n);
}

int	string_map_check(char *s)
{
	char	*tmp;

	tmp = s;
	while (*s)
	{
		if (*s == '1' || *s == '0' || *s == 'S' || *s == 'N'
			|| *s == 'W' || *s == 'E' || *s == ' ' || *s == '\n')
			s++;
		else
			return (0);
	}
	s = tmp;
	return (1);
}
