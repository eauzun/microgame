#include "../includes/so_long.h"

static void	flood_fill(t_map *map, int x, int y, int *visited)
{
	if (x < 0 || x >= map->width || 
		y < 0 || y >= map->height || 
		map->grid[y][x] == '1' || 
		visited[y * map->width + x])
		return;

	visited[y * map->width + x] = 1;

	flood_fill(map, x + 1, y, visited);
	flood_fill(map, x - 1, y, visited);
	flood_fill(map, x, y + 1, visited);
	flood_fill(map, x, y - 1, visited);
}

int	check_path(t_map *map)
{
	int	*visited;
	int	collectibles_found;
	int	exit_found;
	int	i;
	int	j;

	visited = malloc(map->width * map->height * sizeof(int));
	if (!visited)
		return (-1);

	memset(visited, 0, map->width * map->height * sizeof(int));

	flood_fill(map, map->player_x, map->player_y, visited);

	collectibles_found = 0;
	exit_found = 0;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			// Collectible kontrolü
			if (map->grid[i][j] == 'C')
			{
				// Collectible ziyaret edilemiyorsa ve çıkış tarafından bloklanmışsa
				if (!visited[i * map->width + j] && 
					(map->grid[i][j-1] == 'E' || 
					map->grid[i][j+1] == 'E' || 
					map->grid[i-1][j] == 'E' || 
					map->grid[i+1][j] == 'E'))
				{
					free(visited);
					return (-2);
				}
				
				// Normal collectible kontrolü
				if (visited[i * map->width + j])
					collectibles_found++;
			}
			
			// Çıkış kontrolü
			if (map->grid[i][j] == 'E' && visited[i * map->width + j])
				exit_found = 1;
		}
	}

	free(visited);

	if (collectibles_found != map->collectibles)
		return (-2);
	
	if (!exit_found)
		return (-3);

	return (0);
}