#include "../includes/so_long.h"

static int	check_map_rectangular(t_map *map)
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

static int	check_top_bottom_walls(t_map *map)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (map->grid[0][j] != '1' || 
			map->grid[map->height - 1][j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

static int	check_side_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1' || 
			map->grid[i][map->width - 1] != '1')
			return (-1);
		i++;
	}
	return (0);
}

static int	count_map_elements(t_map *map)
{
	int	i;
	int	j;
	int	players;
	int	exits;
	int	collectibles;

	i = -1;
	players = 0;
	exits = 0;
	collectibles = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->grid[i][j] == 'P' && ++players)
			{
				map->player_x = j;
				map->player_y = i;
			}
			else if (map->grid[i][j] == 'E' && ++exits)
			{
				map->exit_x = j;
				map->exit_y = i;
			}
			else if (map->grid[i][j] == 'C')
				collectibles++;
		}
	}
	map->collectibles = collectibles;
	return ((players == 1 && exits == 1 && collectibles > 0) ? 0 : -1);
}

int	map_validate(t_map *map)
{
	if (check_map_rectangular(map) == -1)
	{
		write(2, "Error\nMap is not rectangular\n", 29);
		return (-1);
	}
	if (check_top_bottom_walls(map) == -1)
	{
		write(2, "Error\nTop or bottom row is not surrounded by walls\n", 50);
		return (-1);
	}
	if (check_side_walls(map) == -1)
	{
		write(2, "Error\nSide columns are not surrounded by walls\n", 46);
		return (-1);
	}
	if (count_map_elements(map) == -1)
	{
		write(2, "Error\nInvalid map elements\n", 27);
		return (-1);
	}
	return (0);
}