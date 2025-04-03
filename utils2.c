#include "so_long.h"

void	player_position(char	**map, int *x, int *y, t_demnsions	*w_h)
{
	int	i;
	int	j;
	int	height;
	int	width;

	width = w_h->w;
	height = w_h->h;
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

int	count_collectibles(char **map)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	j = 0;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}

void	flood_fill(char	**map, int x, int y, t_demnsions	*w_h)
{
	if (x < 0 || y < 0 || x >= w_h->w || y >= w_h->h
		|| map[y][x] == '1' || map[y][x] == 'V'
		|| (map[y][x] == 'E' && count_collectibles(map)))
		return ;
	map[y][x] = 'V';
	flood_fill(map, x - 1, y, w_h);
	flood_fill(map, x + 1, y, w_h);
	flood_fill(map, x, y - 1, w_h);
	flood_fill(map, x, y + 1, w_h);
}
