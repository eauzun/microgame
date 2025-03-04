#include"so_long.h"

t_game *load_map(char *file)
{
    t_game  *game;
    int     fd;
    char    *line;
    int     i;

    game = malloc(sizeof(t_game));
    if (!game)
        return (free(game), NULL);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (close(fd), NULL);
    
    game->map = malloc(sizeof(char *) * 100);
    if (!game->map)
        return (free(game->map), NULL);

    i = 0;
    while ((line = get_next_line(fd)))
        game->map[i++] = line;
    game->map[i] = NULL;
    game->map_height = i;
    game->map_width = (i > 0) ? (int)strlen(game->map[0]) - 1 : 0;
    close(fd);
    return (game);
}

void render_map(t_game *game)
{
	int x; 
	int y;
	
	
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