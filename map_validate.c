/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:20:09 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/21 10:39:20 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	count_map_elements_count(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	map->collectibles = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->grid[i][j] == 'P')
				set_player_position(map, j, i);
			else if (map->grid[i][j] == 'E')
				set_exit_position(map, j, i);
			else if (map->grid[i][j] == 'C')
				map->collectibles++;
		}
	}
	return (0);
}

static int	count_map_elements_validate(t_map *map)
{
	int	players;
	int	exits;
	int	i;
	int	j;

	players = 0;
	exits = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->grid[i][j] == 'P')
				players++;
			else if (map->grid[i][j] == 'E')
				exits++;
		}
	}
	if (players == 1 && exits == 1 && map->collectibles > 0)
		return (0);
	return (-1);
}

int	count_map_elements(t_map *map)
{
	int	count_map_elem;
	int	valid_map_elem;

	count_map_elem = count_map_elements_count(map);
	valid_map_elem = count_map_elements_validate(map);
	if (count_map_elem == 0 && valid_map_elem == 0)
		return (0);
	return (-1);
}

int	check_map_walls_and_elements(t_map *map, t_game *game)
{
	if (check_map_rectangular(map) == -1)
	{
		print_error("Map is not rectangular", game);
		return (-1);
	}
	if (check_top_bottom_walls(map) == -1)
	{
		print_error("Top or bottom row is not surrounded by walls game", game);
		return (-1);
	}
	if (check_side_walls(map) == -1)
	{
		print_error("Side columns are not surrounded by walls", game);
		return (-1);
	}
	if (count_map_elements(map) == -1 || validate_map_chars(map->grid) == -1)
	{
		print_error("Invalid map elements", game);
		return (-1);
	}
	return (0);
}

int	map_validate(t_map *map, t_game *game)
{
	int	path_result;

	if (map->width > 59 || map->height > 32)
	{
		print_error("Map resolution is not compatible.", game);
		return (-1);
	}
	if (check_map_walls_and_elements(map, game) == -1)
		return (-1);
	path_result = check_path(map);
	if (path_result == -2)
	{
		print_error("Cannot reach all collectibles", game);
		return (-1);
	}
	if (path_result == -3)
	{
		print_error("Cannot reach exit", game);
		return (-1);
	}
	return (0);
}
