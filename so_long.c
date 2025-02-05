#include "so_long.h"
#include "get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TILE_SIZE 32

typedef struct s_game {
    void    *mlx;
    void    *win;
    void    *wall;
    void    *floor;
    void    *player_up;
    void    *player_down;
    void    *player_left;
    void    *player_right;
    void    *player;
    char    **map;
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
}   t_game;

// Haritayı dosyadan yükleyen fonksiyon
t_game *load_map(char *file)
{
    t_game  *game;
    int     fd;
    char    *line;
    int     i;

    game = malloc(sizeof(t_game));
    if (!game)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (NULL);
    
    game->map = malloc(sizeof(char *) * 100);
    if (!game->map)
        return (NULL);
    
    i = 0;
    while ((line = get_next_line(fd)))
    {
        game->map[i++] = line;
    }
    game->map[i] = NULL;
    game->map_height = i;
    game->map_width = (i > 0) ? (int)strlen(game->map[0]) - 1 : 0;
    close(fd);
    return (game);
}

// Haritayı ekrana çizen fonksiyon
void render_map(t_game *game)
{
    int x, y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * TILE_SIZE, y * TILE_SIZE);
            else
                mlx_put_image_to_window(game->mlx, game->win, game->floor, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->player, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

// Karakterin hareketini kontrol eden fonksiyon
int key_hook(int keycode, t_game *game)
{
    if (!game || !game->mlx || !game->win)
        return (1);
    
    int new_x = game->player_x;
    int new_y = game->player_y;
    
    if (keycode == 119)
    {    
        new_y -= 1;
        game->player = game->player_up;
    }
    if (keycode == 115)
    {
        new_y += 1;
        game->player = game->player_down;
    }
    if (keycode == 97)
    {
        new_x -= 1;
        game->player = game->player_left;
    }
    if (keycode == 100)
    {
        new_x += 1;
        game->player = game->player_right;
    }
    if (keycode == 65307)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    
    if (game->map[new_y][new_x] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
    }
    
    mlx_clear_window(game->mlx, game->win);
    render_map(game);
    
    return (0);
}

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
    game->player_left = mlx_xpm_file_to_image(game->mlx, "textures/player/pacman/pacman-left/1.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_right = mlx_xpm_file_to_image(game->mlx, "textures/player/pacman/pacman-right/1.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_up = mlx_xpm_file_to_image(game->mlx, "textures/player/pacman/pacman-up/1.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    game->player_down = mlx_xpm_file_to_image(game->mlx, "textures/player/pacman/pacman-down/1.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    
    if (!game->wall || !game->floor || !game->player_left || !game->player_right || !game->player_up || !game->player_down)
    {
        printf("Texture yükleme başarısız\n");
        return (1);
    }
    
    game->player = game->player_right;
    game->player_x = 1;
    game->player_y = 1;
    
    render_map(game);
    mlx_hook(game->win, 2, 1L << 0, key_hook, game);
    mlx_loop(game->mlx);
    
    return (0);
}
