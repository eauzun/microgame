/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:30:13 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/19 20:37:34 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_file_extension(char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	if (len < 4)
		return (-1);
	if (file_path[len - 4] != '.'
		|| file_path[len - 3] != 'b'
		|| file_path[len - 2] != 'e'
		|| file_path[len - 1] != 'r')
		return (-1);
	return (0);
}

static int	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

static int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open_file(file_path);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close_file(fd);
	return (lines);
}

static int	read_map_lines(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_newline(line);
		map->grid[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	return (0);
}

int	map_parse(char *file_path, t_map *map)
{
	int		fd;

	map->height = count_lines(file_path);
	if (map->height <= 0)
		return (-1);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (-1);
	fd = open_file(file_path);
	if (fd == -1)
	{
		free(map->grid);
		return (-1);
	}
	if (read_map_lines(fd, map) == -1)
	{
		free(map->grid);
		close_file(fd);
		return (-1);
	}
	map->width = ft_strlen(map->grid[0]);
	close_file(fd);
	return (0);
}
