#include "so_long.h"

int	cheaker(char charcter, int *e, int *p, int *c)
{
	if (charcter == 'E')
		(*e)++;
	else if (charcter == 'P')
		(*p)++;
	else if (charcter == 'C')
		(*c)++;
	else if (charcter != '0' && charcter != '1')
		return (-1);
	return (0);
}

int	validate_map_elements(char	**map)
{
	static int	i;
	static int	j;
	static int	p;
	static int	e;
	static int	c;

	if (!map)
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			cheaker(map[i][j], &e, &p, &c);
			if (cheaker(map[i][j], &e, &p, &c) == -1)
				ft_perror("Error\nInvalid character\n", map, NULL, 0);
			j++;
		}
		i++;
	}
	if (e == 1 && p == 1 && c > 0)
		return (1);
	ft_perror("Error\n1 'E', 1 'P', and at least 1 'C'\n", map, NULL, 0);
	return (0);
}

void	validate_map_borders(char	**map)
{
	static int	i;
	static int	j;
	static int	height;
	static int	width;

	if (!map || !map[0])
		ft_perror("Error\nEmpty map\n", map, NULL, 0);
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	while (j < width)
	{
		if (!map[0][j] || !map[height - 1][j] ||
			map[0][j] != '1' || map[height - 1][j] != '1')
			ft_perror("Error\nInvalid map borders\n", map, NULL, 0);
		j++;
	}
	while (i < height)
	{
		if (!map[i][0] || !map[i][width - 1] ||
			map[i][0] != '1' || map[i][width - 1] != '1')
			ft_perror("Error\nInvalid map borders\n", map, NULL, 0);
		i++;
	}
}

void	validate_map(char	**map)
{
	int	height;
	int	width;

	if (!map || !(*map))
		ft_perror("Error\nEmpty map\n", map, NULL, 0);
	validate_map_elements(map);
	validate_map_borders(map);
	check_lines_len(map);
	height = 0;
	while (map[height])
	{
		width = ft_strlen(map[height]);
		height++;
	}
	validate_player_moves(map, height, width);
}

void	validate_player_moves(char	**map, int height, int width)
{
	int			x;
	int			y;
	char		**map_copy;
	int			i;
	t_demnsions	w_and_h;

	i = 0;
	w_and_h.w = width;
	w_and_h.h = height;
	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		ft_perror("Error\nAllocation failed for map copy\n", map, NULL, 0);
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
			ft_perror("Error\nstrdup failed\n", map, NULL, 0);
		i++;
	}
	map_copy[i] = NULL;
	player_position(map_copy, &x, &y, &w_and_h);
	flood_fill(map_copy, x, y, &w_and_h);
	check_if_still_exit_or_coins(map_copy, height, width);
	free_the_map(map_copy);
}
