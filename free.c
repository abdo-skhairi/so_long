#include "so_long.h"

void	free_the_map(char	**map)
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
}

void	free_all_and_exit(t_game	*my_game, int	**p_position)
{
	ft_delete_images(my_game->mlx, my_game);
	free_the_map(my_game->map);
	if (*p_position)
	{
		free(*p_position);
		*p_position = NULL;
	}
	mlx_terminate(my_game->mlx);
	exit(0);
}

void	ft_perror(char	*error_string, char	**map, char	*content, int fd)
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
	if (fd)
		close(fd);
	write(2, error_string, ft_strlen(error_string));
	exit(1);
}
