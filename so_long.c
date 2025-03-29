#include "so_long.h"

void	ft_perror(char	*error_string, char	**map, char	*content)
{
	int	i;

	i = 0;
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
		ft_perror("Error\nuncorect file name\n", NULL, NULL);
	while (file_name[i])
	{
		if (file_name[i] != ber_str[j])
			ft_perror("Error\nmap file_name sould be <.ber>\n", NULL, NULL);
		i++;
		j++;
	}
}

int	map_len_for_malloc(char *path_name)
{
	int	fd;
	int	line;

	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		ft_perror("Error\nCannot open file\n", NULL, NULL);
	line = 0;
	while (get_next_line(fd))
		line++;
	close(fd);
	return (line);
}

int	ft_open(char	*path_name)
{
	int	fd;

	check_file_name(path_name);
	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		ft_perror("Error\nCannot open file\n", NULL, NULL);
	return (fd);
}
char	**read_map(char *path_name)
{
	char	**map;
	int		fd;
    int		i;
    char	*s;

	i = 0;
	map = malloc(sizeof(char *) * (map_len_for_malloc(path_name) + 1));
	if (!map)
        ft_perror("Error\nAllocation failed\n", NULL, NULL);
	fd = ft_open(path_name);
    while ((s = get_next_line(fd)))
    {
        if (s[0] == '\n')  
        {
            free(s);
            close(fd);
            ft_perror("Error\nEmpty line found in the map\n", map, NULL);
        }
        if (s[ft_strlen(s) - 1] == '\n')
            s[ft_strlen(s) - 1] = '\0';
        map[i] = s;
        i++;
    }
    map[i] = NULL;
    close(fd);
    return (map);
}

void	initilizer(int	*i, int	*j, int	*p, int	*e, int	*c)
{
	*i = 0;
	*j = 0;
	*p = 0;
	*e = 0;
	*c = 0;
}

void	cheaker(char	charcter, int	*e, int	*p, int	*c, char	**map)
{
	if (charcter == 'E')
		(*e)++;
	else if (charcter == 'P')
		(*p)++;
	else if (charcter == 'C')
			(*c)++;
	else if (charcter != '0' && charcter != '1')
			ft_perror("Error\nInvalid character\n", map, NULL);
}

int	validate_map_elements(char	**map)
{
	int	i;
	int	j;
	int	p;
	int	e;
	int	c;

	initilizer(&i, &j, &p, &e, &c);
	if (!map)
		return 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			cheaker(map[i][j], &e, &p, &c, map);
			j++;
		}
		i++;
	}
	if (e == 1 && p == 1 && c > 0)
		return (1);
	ft_perror("Error\nMap must contain exactly 1 'E', 1 'P', and at least 1 'C'\n", map, NULL);
	return (0);
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
			ft_perror("Error\nInvalid map borders\n", map, NULL);
		i++;
	}
}

void	validate_map_borders(char	**map)
{
	int	i;
	int	j;
	int	height;
	int	width;

	i = 0;
	j = 0;
	height = 0;
	if (!map || !map[0])
		ft_perror("Error\nEmpty map\n", map, NULL);
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	while (j < width)
	{
		if (!map[0][j] || !map[height - 1][j] || map[0][j] != '1' || map[height - 1][j] != '1')
			ft_perror("Error\nInvalid map borders\n", map, NULL);
		j++;
	}
	while (i < height)
	{
		if (!map[i][0] || !map[i][width - 1] || map[i][0] != '1' || map[i][width - 1] != '1')
			ft_perror("Error\nInvalid map borders\n", map, NULL);
		i++;
	}
}

void	player_position(char	**map, int *x, int *y, int height, int width)
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
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(char	**map, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || x >= width || y >= height || map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'E')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, height, width);
	flood_fill(map, x - 1, y, height, width);
	flood_fill(map, x, y + 1, height, width);
	flood_fill(map, x, y - 1, height, width);
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
			if (map[i][j] == 'C')
				ft_perror("Error\nInvalid map, unreachable exit or coins\n",
					map, NULL);
			else if (map[i][j] == 'E' && map[i][j + 1] == '1'
					&& map[i][j - 1] == '1'
					&& map[i + 1][j] == '1' && map[i - 1][j] == '1')
				ft_perror("Error\nInvalid map, unreachable exit or coins\n", map, NULL);
			j++;
		}
		i++;
	}
}

void	validate_player_moves(char	**map, int height, int width)
{
	int		x;
	int		y;
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		ft_perror("Error\nAllocation failed for map copy\n", map, NULL);
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
			ft_perror("Error\nstrdup failed\n", map, NULL);
		i++;
	}
	map_copy[i] = NULL;
	player_position(map_copy, &x, &y, height, width);
	flood_fill(map_copy, x, y, height, width);
	check_if_still_exit_or_coins(map_copy, height, width);
	free_the_map(map_copy);
}

void	validate_map(char	**map)
{
	int	height;
	int	width;

	if (!map || !(*map))
		ft_perror("Error\nEmpty map\n", map, NULL);
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

int	main(int ac, char	**av)
{
	char	**map;

	map = NULL;
	if (ac != 2)
		ft_perror("Error\n./so_long <map_path_file>\n", NULL, NULL);
	map = read_map(av[1]);
	validate_map(map);
	ft_game(map);
}
