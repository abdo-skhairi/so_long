/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:48:13 by sabderra          #+#    #+#             */
/*   Updated: 2025/04/03 20:48:16 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_xy	*free_all_and_exit(t_game	*my_game)
{
	ft_delete_images(my_game->mlx, my_game);
	free_the_map(my_game->map);
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
		map = NULL;
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
