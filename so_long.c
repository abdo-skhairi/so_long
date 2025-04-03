/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:48:31 by sabderra          #+#    #+#             */
/*   Updated: 2025/04/03 20:54:03 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map(char *path_name)
{
	static int	i;
	char		**map;
	int			fd;
	char		*s;

	map = malloc(sizeof(char *) * (map_len_for_malloc(path_name) + 1));
	if (!map)
		ft_perror("Error\nAllocation failed\n", NULL, NULL, 0);
	fd = ft_open(path_name);
	s = get_next_line(fd);
	while (s)
	{
		if (s[0] == '\n')
			ft_perror("Error\nEmpty line found in the map\n", map, s, fd);
		if (s[ft_strlen(s) - 1] == '\n')
			s[ft_strlen(s) - 1] = '\0';
		map[i] = s;
		s = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	check_if_still_exit_or_coins(char	**map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'E' && !count_collectibles(map))
				ft_perror("Error\n", map, NULL, 0);
			if (map[i][j] == 'C')
				ft_perror("Error\nInvalid map, unreachable exit or coins\n",
					map, NULL, 0);
			else if (map[i][j] == 'E' && map[i][j + 1] == '1'
					&& map[i][j - 1] == '1'
					&& map[i + 1][j] == '1' && map[i - 1][j] == '1')
				ft_perror("Error\nunreachable E or C\n", map, NULL, 0);
			j++;
		}
		i++;
	}
}

void	ll(void)
{
	system("leaks so_long");
}

int	main(int ac, char	**av)
{
	char	**map;

	atexit(ll);
	map = NULL;
	if (ac != 2)
		ft_perror("Error\n./so_long <map_path_file>\n", NULL, NULL, 0);
	map = read_map(av[1]);
	validate_map(map);
	ft_game(map);
}
