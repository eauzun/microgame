#include "so_long.h"

int main()
{
    t_game *game;
    
    game = load_map("map.ber");
    if (!game)
    {
        printf("Map Nanay\n");
        return (1);
    }
    
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "So_long");
    
    game->wall = mlx_xpm_file_to_image(game->mlx, "textures/environment/wall.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->floor = mlx_xpm_file_to_image(game->mlx, "textures/environment/floor.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_left = mlx_xpm_file_to_image(game->mlx, "textures/player/left.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_right = mlx_xpm_file_to_image(game->mlx, "textures/player/right.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_up = mlx_xpm_file_to_image(game->mlx, "textures/player/up.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_down = mlx_xpm_file_to_image(game->mlx, "textures/player/down.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    
    if (!game->wall || !game->floor || !game->player_left || !game->player_right || !game->player_up || !game->player_down)
    {
        printf("Texture nanay\n");
        return (1);
    }
    
    game->player = game->player_down;
    game->player_x = 1;
    game->player_y = 1;
    
    render_map(game);
    mlx_hook(game->win, 2, 1L << 0, key_hook, game);
    mlx_loop(game->mlx);
    
    return (0);
}
