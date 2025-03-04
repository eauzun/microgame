#include "so_long.h"

int left(t_game *game, int new_x)
{
	new_x -= 1;
	game->player = game->player_left;
	return(new_x);
}

int right(t_game *game, int new_x)
{
	new_x += 1;
	game->player = game->player_right;
	return(new_x);
}

int up(t_game *game, int new_y)
{
	new_y -= 1;
	game->player = game->player_up;
	return(new_y);
}

int down(t_game *game, int new_y)
{
	new_y += 1;
	game->player = game->player_down;
	return(new_y);
}
int key_hook(int keycode, t_game *game)
{
    int new_x;
    int new_y;

    new_x = game->player_x;
    new_y = game->player_y;
    if (!game || !game->mlx || !game->win)
        return (1);
    if (keycode == 119)
        new_y = up(game, new_y);
    if (keycode == 115)
        new_y = down(game, new_y);
    if (keycode == 97)
        new_x = left(game, new_x);
    if (keycode == 100)
        new_x = right(game, new_x);
    if (keycode == 65307)
        interrupt(game);
    if (game->map[new_y][new_x] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
    }
                            
    render_map(game);
    return (0);
}
