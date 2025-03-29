#include "so_long.h"

void ft_delete_textures(t_game *my_game)
{
	if (my_game->player_texture)
		mlx_delete_texture(my_game->player_texture);
	if (my_game->wall_texture)
		mlx_delete_texture(my_game->wall_texture);
	if (my_game->collectible_texture)
		mlx_delete_texture(my_game->collectible_texture);
	if (my_game->exit_texture)
		mlx_delete_texture(my_game->exit_texture);
	if (my_game->space_texture)
		mlx_delete_texture(my_game->space_texture);
}

void ft_delete_images(mlx_t *mlx, t_game *my_game)
{
	int i;

    if (!mlx || !my_game)
        return;
    mlx_image_t **images[] = {
        &my_game->player_img, &my_game->wall_img,
        &my_game->collectible_img, &my_game->exit_img,
        &my_game->space_img, NULL
    };
    i = 0;
    while (images[i])
    {
        if (*images[i])
        {
            mlx_delete_image(mlx, *images[i]);
            *images[i] = NULL;
        }
        i++;
    }
}

void    ft_calculate_dimensions(t_game *my_game, int *width, int *height, char **map)
{
	while(map[(*height)])
		(*height)++;
	while(map[0][(*width)])
		(*width)++;
	my_game->height = (*height);
	my_game->width  = (*width);
}

void    ft_set_images(t_game    *my_game)
{
	int y;
	int x;

	x = 0;
	y = 0;
	while(y < my_game->height)
	{
		x = 0;
		while(my_game->map[y][x])
		{
			if(my_game->map[y][x] == 'P')
				mlx_image_to_window(my_game->mlx, my_game->player_img, x *64, y*64);
			else if(my_game->map[y][x] == '1')
				mlx_image_to_window(my_game->mlx, my_game->wall_img, x *64, y*64);
			else if(my_game->map[y][x] == 'C')
				mlx_image_to_window(my_game->mlx, my_game->collectible_img, x *64, y*64);
			else if(my_game->map[y][x] == 'E')
				mlx_image_to_window(my_game->mlx, my_game->exit_img, x *64, y*64);
			else if(my_game->map[y][x] == '0')
				mlx_image_to_window(my_game->mlx, my_game->space_img, x *64, y*64);
			x++;
		}
		y++;
	}
}

void    ft_get_images(t_game   *my_game)
{
	my_game->player_img = mlx_texture_to_image(my_game->mlx, my_game->player_texture);
	if(!(my_game->player_img))
		ft_perror("Error\n", NULL, NULL);
	my_game->wall_img = mlx_texture_to_image(my_game->mlx, my_game->wall_texture);
	if(!(my_game->wall_img))
		ft_perror("Error\n", NULL, NULL);
	my_game->collectible_img = mlx_texture_to_image(my_game->mlx, my_game->collectible_texture);
	if(!(my_game->collectible_img))
		ft_perror("Error\n", NULL, NULL);
	my_game->exit_img = mlx_texture_to_image(my_game->mlx, my_game->exit_texture);
	if(!(my_game->exit_img))
		ft_perror("Error\n", NULL, NULL);
	my_game->space_img = mlx_texture_to_image(my_game->mlx, my_game->space_texture);
	if(!(my_game->space_img))
		ft_perror("Error\n", NULL, NULL);
}

void    ft_get_textures_and_images(t_game  *my_game)
{
	my_game->player_texture = mlx_load_png("images/player.png");
	if(!(my_game->player_texture))
		ft_perror("Error\n", NULL, NULL);
	my_game->wall_texture = mlx_load_png("images/wall.png");
	if(!(my_game->wall_texture))
		ft_perror("Error\n", NULL, NULL);
	my_game->collectible_texture = mlx_load_png("images/collectible.png");
	if(!(my_game->collectible_texture))
		ft_perror("Error\n", NULL, NULL);
	my_game->exit_texture = mlx_load_png("images/exit.png");
	if(!(my_game->exit_texture))
		ft_perror("Error\n", NULL, NULL);
	my_game->space_texture = mlx_load_png("images/space.png");
	if(!(my_game->space_texture))
		ft_perror("Error\n", NULL, NULL);
	ft_get_images(my_game);
}

void    ft_init_game(t_game    *my_game, char **map)
{
	int width;
	int height;

	width = 0;
	height = 0;
	ft_calculate_dimensions(my_game, &width, &height, map);
	my_game->map = map;
	my_game->moves_counter = 0;
	my_game->mlx = mlx_init(width*64, height*64, "so_long", 1);
	if(!(my_game->mlx))
		ft_perror("game_error", NULL, NULL);
	ft_get_textures_and_images(my_game);
}

void	ft_put_numbr(int n)
{
	char	c;

	c = n + 48;
	if(n == 0)
		write(1, "0", 1);
	if(n > 9)
		ft_put_numbr(n / 10);
	c = (n % 10) + 48;
	write(1, &c, 1);
}

int	count_collectibles(t_game	*my_game)
{
	char **map;
	int i;
	int j;
	int counter;
	
	i = 0;
	j = 0;
	counter = 0;
	map = my_game->map;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'C')
				counter++;
			j++;
		}
		i++;
	}
	return(counter);
}

int	*player_x_y(t_game *my_game)
{
	int	*positions;
	int	i;
	int	j;

	positions = malloc(sizeof(int) * 2);
	if(!positions)
		return(NULL);
	i = 0;
	while(i < my_game->height)
	{
		j = 0;
		while(j < my_game->width)
		{
			if(my_game->map[i][j] == 'P')
			{
				positions[0] = j;
				positions[1] = i;
				return(positions);
			}
			j++;
		}
		i++;
	}
	free(positions);
	return(NULL);
}

void	free_the_map(char **map)
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
}

void	free_all_and_exit(t_game *my_game, int **p_position)
{
	ft_delete_images(my_game->mlx, my_game);
	free_the_map(my_game->map);
	if(*p_position)
	{
		free(*p_position);
		*p_position = NULL;
	}
	mlx_terminate(my_game->mlx);
	exit(0);
}

void	movement(t_game	*my_game, int new_x, int new_y, int **p_position)
{
	if(my_game->map[new_y][new_x] == 'E' && !my_game->collectibles_score)
	{
		write(1, "congratulation you win🎉🥳🎊🎁\n", 40);
		free_all_and_exit(my_game, p_position);
		exit(0);
	}
	if(my_game->map[new_y][new_x] != '1' && my_game->map[new_y][new_x] != 'E')
	{
		if(my_game->map[new_y][new_x] == 'C')
			(my_game->collectibles_score)--;
		mlx_image_to_window(my_game->mlx, my_game->space_img, my_game->player_x * 64, my_game->player_y * 64);
		mlx_image_to_window(my_game->mlx, my_game->player_img, new_x*64, new_y*64);
		my_game->map[my_game->player_y][my_game->player_x] = '0';
		my_game->map[new_y][new_x] = 'P';
		my_game->moves_counter++;
		if(my_game->map[new_y][new_x] != '1')
		{
			write(1, "Move number ", 11);
			ft_put_numbr(my_game->moves_counter);
			write(1, ":\n", 3);
		}
	}
}

void	handler(mlx_key_data_t	key_presed, void	*ptr_to_my_game)
{
	t_game	*my_game;
	int		*p_position;

	my_game = (t_game *)ptr_to_my_game;
	p_position = player_x_y(my_game);
	my_game->player_x = p_position[0];
	my_game->player_y = p_position[1];
	my_game->collectibles_score = count_collectibles(my_game);
	if(key_presed.action)
	{
		if(key_presed.key == MLX_KEY_RIGHT || key_presed.key == MLX_KEY_D)
			movement(my_game, my_game->player_x + 1, my_game->player_y, &p_position);
		else if(key_presed.key == MLX_KEY_LEFT || key_presed.key == MLX_KEY_A)
			movement(my_game, my_game->player_x - 1, my_game->player_y, &p_position);
		else if(key_presed.key == MLX_KEY_UP || key_presed.key == MLX_KEY_W)
			movement(my_game, my_game->player_x, my_game->player_y - 1, &p_position);
		else if(key_presed.key == MLX_KEY_DOWN || key_presed.key == MLX_KEY_S)
			movement(my_game, my_game->player_x, my_game->player_y + 1, &p_position);
		else if(key_presed.key == MLX_KEY_ESCAPE)
			free_all_and_exit(my_game, &p_position);
	}

}

void    ft_game(char    **map)
{
	t_game  my_game;

	ft_init_game(&my_game, map);
	ft_set_images(&my_game);
	mlx_key_hook(my_game.mlx, &handler, &my_game);
	mlx_loop(my_game.mlx);
	ft_delete_images(my_game.mlx, &my_game);
	mlx_terminate(my_game.mlx);
}
