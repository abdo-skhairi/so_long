/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:48:38 by sabderra          #+#    #+#             */
/*   Updated: 2025/04/03 20:50:45 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define MAX_LINES 2

# include "/Users/sabderra/Desktop/MLX42/include/MLX42/MLX42.h"
# include "get_next_line_bonus.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*exit_texture;
	mlx_texture_t	*space_texture;
	mlx_image_t		*player_img;
	mlx_image_t		*wall_img;
	mlx_image_t		*collectible_img;
	mlx_image_t		*exit_img;
	mlx_image_t		*space_img;
	char			**map;
	int				player_x;
	int				player_y;
	int				collectibles_score;
	int				width;
	int				height;
	int				moves_counter;
}	t_game;

typedef struct w_and_h
{
	int	w;
	int	h;
}	t_demnsions;

typedef struct x_and_y
{
	int	x;
	int	y;
}	t_xy;

void	check_file_name(char *file_name);
void	check_lines_len(char **map);
void	check_if_still_exit_or_coins(char **map, int height, int width);
int		cheaker(char charcter, int *e, int *p, int *c);
void	check_if_exit_block_map(char **map);

char	**read_map(char *path_name);
int		validate_map_elements(char **map);
void	validate_map_borders(char **map);
void	validate_player_moves(char **map, int height, int width);
void	validate_map_borders(char	**map);
void	validate_map(char	**map);

void	player_position(char	**map, int *x, int *y, t_demnsions	*w_h);
void	flood_fill(char	**map, int x, int y, t_demnsions	*w_h);
void	free_the_map(char **map);
void	ft_put_numbr(int n);
t_xy	*player_x_y(t_game	*my_game);
int		ft_open(char	*path_name);

void	ft_game(char **map);
void	init_game(t_game	*my_game, char **map);
void	ft_get_textures_and_images(t_game	*my_game);
void	ft_set_images(t_game	*my_game);
int		map_len_for_malloc(char *path_name);
void	ft_get_images(t_game	*my_game);
void	ft_delete_images(mlx_t	*mlx, t_game	*my_game);
void	ft_delete_textures(t_game	*my_game);

void	handler(mlx_key_data_t	key_presed, void	*ptr_to_my_game);
void	movement(t_game	*my_game, int new_x, int new_y);

void	ft_calculate_dimensions(t_game *my_game, int *width, int *height,
			char **map);

int		count_collectibles(char **map);
t_xy	*free_all_and_exit(t_game	*my_game);

void	ft_perror(char	*error_string, char	**map, char	*content, int fd);
void	print_map(char **map);

#endif