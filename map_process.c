#include "get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define TILE_SIZE 32

typedef struct s_game {
    void    *mlx;
    void    *win;
    void    *wall;
    void    *floor;
    char    **map;
    int     map_width;
    int     map_height;
}   t_game;


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
    
    if (!game->wall || !game->floor)
    {
		if(!game->wall)
        	printf("duvar nanay");
		else
			printf("zemin nanay");
        return (1);
    }
    
    render_map(game);
    mlx_loop(game->mlx);
    return (0);
}
