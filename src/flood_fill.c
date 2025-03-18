/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:29:53 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/18 23:59:48 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	flood_fill_with_checks(t_map *map, int x, int y,
	int *visited, int *collected)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height
		|| map->grid[y][x] == '1' || visited[y * map->width + x])
		return (0);
	visited[y * map->width + x] = 1;
	if (map->grid[y][x] == 'C')
		(*collected)++;
	if (map->grid[y][x] == 'E')
		return (1);
	if (flood_fill_with_checks(map, x + 1, y, visited, collected)
		|| flood_fill_with_checks(map, x - 1, y, visited, collected)
		|| flood_fill_with_checks(map, x, y + 1, visited, collected)
		|| flood_fill_with_checks(map, x, y - 1, visited, collected))
		return (1);
	return (0);
}

int	check_path(t_map *map)
{
	int	*visited;
	int	collected;
	int	exit_reached;

	collected = 0;
	exit_reached = 0;
	visited = malloc(map->width * map->height * sizeof(int));
	if (!visited)
		return (-1);
	memset(visited, 0, map->width * map->height * sizeof(int));
	exit_reached = flood_fill_with_checks(map, map->player_x,
        map->player_y, visited, &collected);
	free(visited);
	if (collected < map->collectibles)
		return (-2);
	if (!exit_reached)
		return (-3);
	return (0);
}

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
