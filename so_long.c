#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 768

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*player_up;
	void	*player_down;
	void	*player_left;
	void	*player_right;
	void	*player;
	int		player_x;
	int		player_y;
}	t_game;

void    *map_init()
{
    
}

int key_hook(int keycode, t_game *game)
{

    if (!game || !game->mlx || !game->win)
    {
        return (1);
    }

    printf("nigger:,( %d\n", keycode);

    if (keycode == 119)
    {    
		game->player_y -= 10;
		game->player = game->player_up;
	}
    if (keycode == 115)
	{
        game->player_y += 10;
		game->player = game->player_down;
	}
    if (keycode == 97)
    {
		game->player_x -= 10;
		game->player = game->player_left;
	}
    if (keycode == 100)
	{
        game->player_x += 10;
		game->player = game->player_right;
	}
    if (keycode == 65307)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }

    mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->player, game->player_x, game->player_y);

    return (0);
}

int main()
{
    t_game game;
    int img_width, img_height;
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        return (1);
    }

    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Pac-Man Test");
    if (!game.win)
    {
		printf("window nanay");
        return (1);
    }
	
	game.player_left = mlx_xpm_file_to_image(game.mlx, "textures/player/pacman/pacman-left/1.xpm", &img_width, &img_height);
    game.player_right = mlx_xpm_file_to_image(game.mlx, "textures/player/pacman/pacman-right/1.xpm", &img_width, &img_height);
	game.player_up = mlx_xpm_file_to_image(game.mlx, "textures/player/pacman/pacman-up/1.xpm", &img_width, &img_height);
	game.player_down = mlx_xpm_file_to_image(game.mlx, "textures/player/pacman/pacman-down/1.xpm", &img_width, &img_height);
    if (!game.player_right ||!game.player_left ||!game.player_up ||!game.player_down)
    {
		printf("playerlar nanay");
        return (1);
    }
    game.player_x = WIDTH / 2;
    game.player_y = HEIGHT / 2;

    mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
    mlx_loop(game.mlx);

    return (0);
}
