#include "../includes/so_long.h"

void game_render(t_game *game)
{
    int x, y;

    for (y = 0; y < game->map->height; y++)
    {
        for (x = 0; x < game->map->width; x++)
        {
            if (game->map->grid[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, 
                                        game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map->grid[y][x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, 
                                        game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map->grid[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, 
                                        game->player_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map->grid[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, 
                                        game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
            else if(game->map->grid[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}