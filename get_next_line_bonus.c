/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabderra <sabderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:14:31 by sabderra          #+#    #+#             */
/*   Updated: 2024/12/02 20:05:12 by sabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	func_free(char **str1, char **str2)
{
	if (str1)
	{
		free (*str1);
		*str1 = NULL;
	}
	if (str2)
	{
		free (*str2);
		*str2 = NULL;
	}
}

static char	*ft_rest(char	*storage)
{
	char	*rest;
	int		i;
	int		j;

	i = strc(storage);
	if (i == -1)
		return (NULL);
	j = 0;
	rest = ft_calloc(ft_strlen(storage) - i, 1);
	if (!rest)
	{
		free (storage);
		storage = NULL;
		return (NULL);
	}
	i++;
	while (storage[i])
		rest[j++] = storage[i++];
	free (storage);
	storage = NULL;
	return (rest);
}

static char	*ft_line(char *storage)
{
	char	*line;
	int		i;

	if (!storage)
		return (NULL);
	i = strc (storage);
	if (i == -1)
		return (storage);
	line = ft_calloc(i + 2, 1);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	while (i >= 0)
	{
		line[i] = storage[i];
		i--;
	}
	return (line);
}

static void	ft_read(char **storage, int fd)
{
	char	*buff;
	int		i;
	char	*tmp;

	if (!storage)
		return ;
	i = 1;
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return ;
	while (strc(buff) == -1 && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			break ;
		buff[i] = '\0';
		tmp = *storage;
		*storage = ft_strjoin(tmp, buff);
		func_free(&tmp, NULL);
		if (!*storage)
			break ;
	}
	if (i < 0)
		return (func_free(storage, &buff));
	func_free (&buff, NULL);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read(&storage[fd], fd);
	if (!storage[fd] || !*storage[fd])
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	line = ft_line(storage[fd]);
	storage[fd] = ft_rest(storage[fd]);
	return (line);
}
