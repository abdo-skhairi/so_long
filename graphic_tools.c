#include "so_long.h"

void	ft_calculate_dimensions(t_game	*my_game, int *width, int *height,
	char	**map)
{
	while (map[(*height)])
		(*height)++;
	while (map[0][(*width)])
		(*width)++;
	my_game->height = (*height);
	my_game->width = (*width);
}

void	ft_seter(t_game *my_game, mlx_image_t **images, int x, int y)
{
	if (my_game->map[y][x] == 'P')
		mlx_image_to_window(my_game->mlx, images[0], x * 64, y * 64);
	else if (my_game->map[y][x] == '1')
		mlx_image_to_window(my_game->mlx, images[1], x * 64, y * 64);
	else if (my_game->map[y][x] == 'C')
		mlx_image_to_window(my_game->mlx, images[2], x * 64, y * 64);
	else if (my_game->map[y][x] == 'E')
		mlx_image_to_window(my_game->mlx, images[3], x * 64, y * 64);
	else if (my_game->map[y][x] == '0')
		mlx_image_to_window(my_game->mlx, images[4], x * 64, y * 64);
}

void	ft_set_images(t_game *my_game)
{
	mlx_image_t	*images[5];
	int			x;
	int			y;

	images[0] = my_game->player_img;
	images[1] = my_game->wall_img;
	images[2] = my_game->collectible_img;
	images[3] = my_game->exit_img;
	images[4] = my_game->space_img;
	y = 0;
	while (y < my_game->height)
	{
		x = 0;
		while (my_game->map[y][x])
		{
			ft_seter(my_game, images, x, y);
			x++;
		}
		y++;
	}
}

void	ft_put_numbr(int n)
{
	char	c;

	c = n + 48;
	if (n == 0)
		write(1, "0", 1);
	if (n > 9)
		ft_put_numbr(n / 10);
	c = (n % 10) + 48;
	write(1, &c, 1);
}

int	*player_x_y(t_game	*my_game)
{
	int	*positions;
	int	i;
	int	j;

	positions = malloc(sizeof(int) * 2);
	if (!positions)
		return (NULL);
	i = 0;
	while (i < my_game->height)
	{
		j = 0;
		while (j < my_game->width)
		{
			if (my_game->map[i][j] == 'P')
			{
				positions[0] = j;
				positions[1] = i;
				return (positions);
			}
			j++;
		}
		i++;
	}
	free(positions);
	return (NULL);
}
