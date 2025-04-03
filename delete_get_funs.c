#include "so_long.h"

void	ft_delete_textures(t_game	*my_game)
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

void	ft_delete_images(mlx_t	*mlx, t_game	*my_game)
{
	int			i;
	mlx_image_t	**images[6];

	if (!mlx || !my_game)
		return ;
	images[0] = &my_game->player_img;
	images[1] = &my_game->wall_img;
	images[2] = &my_game->collectible_img;
	images[3] = &my_game->exit_img;
	images[4] = &my_game->space_img;
	images[5] = NULL;
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

void	ft_get_images(t_game	*my_game)
{
	mlx_texture_t	*textures[5];
	mlx_image_t		**images[5];
	int				i;

	textures[0] = my_game->player_texture;
	textures[1] = my_game->wall_texture;
	textures[2] = my_game->collectible_texture;
	textures[3] = my_game->exit_texture;
	textures[4] = my_game->space_texture;
	images[0] = &my_game->player_img;
	images[1] = &my_game->wall_img;
	images[2] = &my_game->collectible_img;
	images[3] = &my_game->exit_img;
	images[4] = &my_game->space_img;
	i = 0;
	while (i < 5)
	{
		*images[i] = mlx_texture_to_image(my_game->mlx, textures[i]);
		if (!(*images[i]))
			ft_perror("Error\n", NULL, NULL, 0);
		i++;
	}
}

void	ft_get_textures_and_images(t_game	*my_game)
{
	my_game->player_texture = mlx_load_png("images/player.png");
	if (!(my_game->player_texture))
		ft_perror("Error\n", NULL, NULL, 0);
	my_game->wall_texture = mlx_load_png("images/wall.png");
	if (!(my_game->wall_texture))
		ft_perror("Error\n", NULL, NULL, 0);
	my_game->collectible_texture = mlx_load_png("images/collectible.png");
	if (!(my_game->collectible_texture))
		ft_perror("Error\n", NULL, NULL, 0);
	my_game->exit_texture = mlx_load_png("images/exit.png");
	if (!(my_game->exit_texture))
		ft_perror("Error\n", NULL, NULL, 0);
	my_game->space_texture = mlx_load_png("images/space.png");
	if (!(my_game->space_texture))
		ft_perror("Error\n", NULL, NULL, 0);
	ft_get_images(my_game);
	ft_delete_textures(my_game);
}
