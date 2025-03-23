/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:23:40 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/21 10:31:06 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static void	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width
		|| y < 0 || y >= map->height
		|| map->grid[y][x] == '1'
		|| map->visited[y * map->width + x])
		return ;
	map->visited[y * map->width + x] = 1;
	if (map->grid[y][x] == 'C')
		map->collected++;
	if (map->grid[y][x] != 'E')
	{
		flood_fill(map, x + 1, y);
		flood_fill(map, x - 1, y);
		flood_fill(map, x, y + 1);
		flood_fill(map, x, y - 1);
	}
}

int	check_path(t_map *map)
{
	int	exit_reached;

	exit_reached = 0;
	map->collected = 0;
	map->visited = malloc(map->width * map->height * sizeof(int));
	if (!map->visited)
		return (-1);
	memset(map->visited, 0, map->width * map->height * sizeof(int));
	flood_fill(map, map->player_x, map->player_y);
	if (map->visited[map->exit_y * map->width + map->exit_x])
		exit_reached = 1;
	free(map->visited);
	map->visited = NULL;
	if (map->collected < map->collectibles)
		return (-2);
	if (!exit_reached)
		return (-3);
	return (0);
}

int	validate_map_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'C' && map[i][j] != 'P'
				&& map[i][j] != 'E' && map[i][j] != '1'
				&& map[i][j] != '0')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
