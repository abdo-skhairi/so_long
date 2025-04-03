/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:47:52 by sabderra          #+#    #+#             */
/*   Updated: 2025/04/03 20:50:02 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement(t_game	*my_game, int new_x, int new_y)
{
	my_game->collectibles_score = count_collectibles(my_game->map);
	if (my_game->map[new_y][new_x] == 'E' && !my_game->collectibles_score)
	{
		write(1, "congratulation you win🎉🥳🎊🎁\n", 40);
		free_all_and_exit(my_game);
		exit(0);
	}
	if (my_game->map[new_y][new_x] != '1' && my_game->map[new_y][new_x] != 'E')
	{
		if (my_game->map[new_y][new_x] == 'C')
			(my_game->collectibles_score)--;
		mlx_image_to_window(my_game->mlx, my_game->space_img,
			my_game->player_x * 64, my_game->player_y * 64);
		mlx_image_to_window(my_game->mlx, my_game->player_img,
			new_x * 64, new_y * 64);
		my_game->map[my_game->player_y][my_game->player_x] = '0';
		my_game->map[new_y][new_x] = 'P';
		my_game->moves_counter++;
		if (my_game->map[new_y][new_x] != '1')
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
	t_xy	*position;

	my_game = (t_game *)ptr_to_my_game;
	position = player_x_y(my_game);
	my_game->player_x = position->x;
	my_game->player_y = position->y;
	if (key_presed.action)
	{
		if (key_presed.key == MLX_KEY_RIGHT || key_presed.key == MLX_KEY_D)
			movement(my_game, my_game->player_x + 1,
				my_game->player_y);
		else if (key_presed.key == MLX_KEY_LEFT || key_presed.key == MLX_KEY_A)
			movement(my_game, my_game->player_x - 1,
				my_game->player_y);
		else if (key_presed.key == MLX_KEY_UP || key_presed.key == MLX_KEY_W)
			movement(my_game, my_game->player_x,
				my_game->player_y - 1);
		else if (key_presed.key == MLX_KEY_DOWN || key_presed.key == MLX_KEY_S)
			movement(my_game, my_game->player_x,
				my_game->player_y + 1);
		else if (key_presed.key == MLX_KEY_ESCAPE)
			free_all_and_exit(my_game);
	}
}

void	ft_init_game(t_game	*my_game, char	**map)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	ft_calculate_dimensions(my_game, &width, &height, map);
	my_game->map = map;
	my_game->moves_counter = 0;
	my_game->mlx = mlx_init(width * 64, height * 64, "so_long", 1);
	if (!(my_game->mlx))
		ft_perror("game_error", NULL, NULL, 0);
	ft_get_textures_and_images(my_game);
}

void	ft_game(char	**map)
{
	t_game	my_game;

	ft_init_game(&my_game, map);
	ft_set_images(&my_game);
	mlx_key_hook(my_game.mlx, &handler, &my_game);
	mlx_loop(my_game.mlx);
	ft_delete_images(my_game.mlx, &my_game);
	mlx_terminate(my_game.mlx);
}
