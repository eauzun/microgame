#include "../includes/so_long.h"

static int flood_fill_with_checks(t_map *map, int x, int y, int *visited, int *collected)
{
    if (x < 0 || x >= map->width || 
        y < 0 || y >= map->height || 
        map->grid[y][x] == '1' || 
        visited[y * map->width + x])
        return 0;

    visited[y * map->width + x] = 1;
    if (map->grid[y][x] == 'C')
        (*collected)++;
    if (map->grid[y][x] == 'E')
        return 1;

    int result = 0;
    result += flood_fill_with_checks(map, x + 1, y, visited, collected);
    result += flood_fill_with_checks(map, x - 1, y, visited, collected);
    result += flood_fill_with_checks(map, x, y + 1, visited, collected);
    result += flood_fill_with_checks(map, x, y - 1, visited, collected);

    return result;
}

int check_path(t_map *map)
{
    int *visited;
    int collected = 0;
    int exit_reached = 0;

    visited = malloc(map->width * map->height * sizeof(int));
    if (!visited)
        return -1;
    memset(visited, 0, map->width * map->height * sizeof(int));

    exit_reached = flood_fill_with_checks(map, map->player_x, map->player_y, visited, &collected);
    free(visited);
    if (collected < map->collectibles)
        return -2;
    if (!exit_reached)
        return -3;
    return 0;
}