/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 23:14:18 by qlentz            #+#    #+#             */
/*   Updated: 2023/03/31 23:55:36 by qlentz           ###   ########.fr       */
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
		fatal_error("failed to open map");
	if (!read_params(fd, p))
		fatal_error("Problem with parameters");
	if (!parse_colors(p))
		fatal_error("Problem with F or C colors");
	set_params(player, &player->texes, p);
	size = check_char_map(p, fd);
	if (size == 0)
		fatal_error("Wrong char in map");
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
