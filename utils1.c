/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:48:45 by sabderra          #+#    #+#             */
/*   Updated: 2025/04/04 18:07:14 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file_name(char	*file_name)
{
	int		i;
	int		j;
	char	*ber_str;

	ber_str = ".ber";
	j = 0;
	i = 0;
	while (file_name[i])
		i++;
	while (i > 0)
	{
		if (file_name[i] == '.' && file_name[i - 1] != '.')
			break ;
		i--;
	}
	if (i == 0)
		ft_perror("Error\nuncorect file name\n", NULL, NULL, 0);
	while (file_name[i])
	{
		if (file_name[i] != ber_str[j])
			ft_perror("Error\nmap file_name sould be <.ber>\n", NULL, NULL, 0);
		i++;
		j++;
	}
}

int	map_len_for_malloc(char *path_name)
{
	int		fd;
	int		line;
	char	*s;

	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		ft_perror("Error\nCannot open file\n", NULL, NULL, 0);
	line = 0;
	s = get_next_line(fd);
	while (s)
	{
		free(s);
		line++;
		s = get_next_line(fd);
	}
	close(fd);
	return (line);
}

int	ft_open(char	*path_name)
{
	int	fd;

	check_file_name(path_name);
	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		ft_perror("Error\nCannot open file\n", NULL, NULL, 0);
	return (fd);
}

void	check_lines_len(char	**map)
{
	int	width;
	int	i;

	width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			ft_perror("Error\nInvalid map borders\n", map, NULL, 0);
		i++;
	}
}
