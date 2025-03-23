/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:56:24 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/19 19:39:34 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/so_long.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	close_file(int fd)
{
	if (fd != -1)
		close(fd);
}

int	check_map_rectangular(t_map *map)
{
	int		i;
	size_t	first_line_len;
	size_t	current_line_len;

	first_line_len = ft_strlen(map->grid[0]);
	i = 1;
	while (i < map->height)
	{
		current_line_len = ft_strlen(map->grid[i]);
		if (current_line_len != first_line_len)
			return (-1);
		i++;
	}
	map->width = (int)first_line_len;
	return (0);
}

int	check_top_bottom_walls(t_map *map)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (map->grid[0][j] != '1' || map->grid[map->height - 1][j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

int	check_side_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			return (-1);
		i++;
	}
	return (0);
}
