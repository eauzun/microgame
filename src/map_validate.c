/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:30:16 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/18 23:53:43 by emuzun           ###   ########.fr       */
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
			{
				map->player_x = j;
				map->player_y = i;
			}
			else if (map->grid[i][j] == 'E')
			{
				map->exit_x = j;
				map->exit_y = i;
			}
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

	i = 0;
	j = 0;
	players = 0;
	exits = 0;
	while (i++ < map->height)
	{
		while (j++ < map->width)
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

int	check_map_walls_and_elements(t_map *map)
{
	if (check_map_rectangular(map) == -1)
	{
		print_error("Map is not rectangular");
		return (-1);
	}
	if (check_top_bottom_walls(map) == -1)
	{
		print_error("Top or bottom row is not surrounded by walls");
		return (-1);
	}
	if (check_side_walls(map) == -1)
	{
		print_error("Side columns are not surrounded by walls");
		return (-1);
	}
	if (count_map_elements(map) == -1)
	{
		print_error("Invalid map elements");
		return (-1);
	}
	return (0);
}

int	map_validate(t_map *map)
{
	int	path_result;

	if (check_map_walls_and_elements(map) == -1)
		return (-1);
	path_result = check_path(map);
	if (path_result == -2)
	{
		print_error("Cannot reach all collectibles");
		return (-1);
	}
	if (path_result == -3)
	{
		print_error("Cannot reach exit");
		return (-1);
	}
	return (0);
}
