#include "so_long.h"

void ft_perror(char *error_string, char **map, char *content)
{
	int i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map);
	}
	if (content)
	{
		free(content);
		content = NULL;
	}
	

	write(2, error_string, ft_strlen(error_string));
	exit(1);
}

void    check_file_name(char    *file_name)
{
	int		i;
	int		j;
	char	*ber_str;

	ber_str = ".ber";
	j = 0;
	i = 0;
	while(file_name[i])
		i++;
	while(i > 0)
	{
		if(file_name[i] == '.' && file_name[i - 1] != '.')
			break;
		i--;
	}
	if(i == 0)
		ft_perror("uncorect file name\n", NULL, NULL);
	while(file_name[i])
	{
		if(file_name[i] != ber_str[j])
			ft_perror("map file_name sould be <.ber>\n", NULL, NULL);
		i++;
		j++;
	}
}

char **read_map(char *path_name)
{
	char **map;
	int fd;
	int i = 0;

	check_file_name(path_name);
	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: Cannot open file\n", NULL, NULL);

	map = malloc(sizeof(char *) * (MAX_LINES + 1));
	if (!map)
		ft_perror("Error: Allocation failed\n", NULL, NULL);

	char *s = get_next_line(fd);
	while (s)
	{
		if (s[0] == '\n')
			ft_perror("Error: Empty line found in the map\n", map, NULL);
		if (s[ft_strlen(s) - 1] == '\n')
			s[ft_strlen(s) - 1] = '\0';
		map[i] = s;
		s = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return map;
}

int validate_map_elements(char **map)
{
	int i = 0, j, E = 0, P = 0, C = 0;

	if (!map)
		return 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '\n')
			{
				if (map[i][j] == 'E')
					E++;
				else if (map[i][j] == 'P')
					P++;
				else if (map[i][j] == 'C')
					C++;
				else if (map[i][j] != '0' && map[i][j] != '1')
				{
					ft_perror("Error: Invalid character\n", NULL, NULL);
					return 0;
				}
			}
			j++;
		}
		i++;
	}
	if (E == 1 && P == 1 && C > 0)
		return 1;
	ft_perror("Error: Map must contain exactly 1 'E', 1 'P', and at least 1 'C'\n", NULL, NULL);
	return 0;
}

void check_lines_len(char **map)
{
	int width;
	int i;

	width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			ft_perror("Error: Invalid map borders\n", map, NULL);
		i++;
	}
}

void validate_map_borders(char **map)
{
	int i = 0;
	int j = 0;
	int height = 0;
	int width;

	if (!map || !map[0])
		ft_perror("Error: Empty map\n", map, NULL);
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	while (j < width)
	{
		if (!map[0][j] || !map[height - 1][j] || map[0][j] != '1' || map[height - 1][j] != '1')
			ft_perror("Error: Invalid map borders\n", map, NULL);
		j++;
	}
	while (i < height)
	{
		if (!map[i][0] || !map[i][width - 1] || map[i][0] != '1' || map[i][width - 1] != '1')
			ft_perror("Error: Invalid map borders\n", map, NULL);
		i++;
	}
}

void player_position(char **map, int *x, int *y, int height, int width)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return;
			}
			j++;
		}
		i++;
	}
}

void flood_fill(char **map, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || x >= width || y >= height || map[y][x] == '1' || map[y][x] == 'V')
		return;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, height, width);
	flood_fill(map, x - 1, y, height, width);
	flood_fill(map, x, y + 1, height, width);
	flood_fill(map, x, y - 1, height, width);
}

void check_if_still_exit_or_coins(char **map, int height, int width)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'E' || map[i][j] == 'C')
				ft_perror("Error: Invalid map, unreachable exit or coins\n", map, NULL);
			j++;
		}
		i++;
	}
}

void validate_player_moves(char **map, int height, int width)
{
	int x;
	int y;
	char **map_copy = malloc(sizeof(char *) * (height + 1));
	int i = 0;

	if (!map_copy)
		ft_perror("Error: Allocation failed for map copy\n", map, NULL);
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
			ft_perror("Error: strdup failed\n", map, NULL);
		i++;
	}
	map_copy[i] = NULL;
	player_position(map_copy, &x, &y, height, width);
	flood_fill(map_copy, x, y, height, width);
	check_if_still_exit_or_coins(map_copy, height, width);
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

void validate_map(char **map)
{
	int height;
	int width;

	if (!map || !(*map))
		ft_perror("Error: Empty map\n", map, *map);

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

int main(int ac, char **av)
{
	char **map = NULL;

	if (ac != 2)
		ft_perror("Error: ./so_long <map_path_file>\n", NULL, NULL);
	map = read_map(av[1]);
	validate_map(map);
	ft_game(map);
}
