#ifndef SO_LONG_H
#define SO_LONG_H

#define MAX_LINES 1000

#include "./MLX42/include/MLX42/MLX42.h"
#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>

typedef struct  s_game
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

void	ft_perror(char *error_string, char **map, char *content);
void	check_file_name(char *file_name);
char    **read_map(char *path_name);
int     validate_map_elements(char **map);
void    check_lines_len(char **map);
void    validate_map_borders(char **map);
void    player_position(char **map, int *x, int *y, int height, int width);
void    flood_fill(char **map, int x, int y, int height, int width);
void    check_if_still_exit_or_coins(char **map, int height, int width);
void    validate_player_moves(char **map, int height, int width);
void    validate_map(char **map);
void    ft_game(char **map);
void    init_game(t_game    *my_game, char **map);
void    calculate_dementions(int *width, int *height, char **map);

#endif