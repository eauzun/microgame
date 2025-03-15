#include "../includes/so_long.h"

#include "so_long.h"


static int	can_move(t_game *game, int new_x, int new_y)

{

	// Duvar kontrolü

	if (game->map->grid[new_y][new_x] == '1')

		return (0);


	// Çıkış kontrolü

	if (game->map->grid[new_y][new_x] == 'E')

	{

		if (game->map->collectibles > 0)

			return (0);

		

		write(1, "Congratulations! You won!\n", 26);

		exit(0);

	}


	return (1);

}


static void	collect_item(t_game *game, int new_x, int new_y)

{

	if (game->map->grid[new_y][new_x] == 'C')

	{

		game->map->grid[new_y][new_x] = '0';

		game->map->collectibles--;

		

		// Konsola kalan collectible sayısını yazdır

		write(1, "Collectibles left: ", 19);

		ft_putnbr(game->map->collectibles);

		write(1, "\n", 1);

	}

}


void	move_player(t_game *game, int dx, int dy)

{

	int	new_x;

	int	new_y;


	new_x = game->map->player_x + dx;

	new_y = game->map->player_y + dy;


	if (!can_move(game, new_x, new_y))

		return;


	// Collectible toplama

	collect_item(game, new_x, new_y);


	// Oyuncu konumunu güncelle

	game->map->grid[game->map->player_y][game->map->player_x] = '0';

	game->map->grid[new_y][new_x] = 'P';

	game->map->player_x = new_x;

	game->map->player_y = new_y;


	// Hareket sayısını artır ve konsola yazdır

	game->moves++;

	write(1, "Moves: ", 7);

	ft_putnbr(game->moves);

	write(1, "\n", 1);


	// Ekranı yeniden çiz

	game_render(game);

}

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }

    if (keycode == W_KEY)
        move_player(game, 0, -1);
    else if (keycode == A_KEY)
        move_player(game, -1, 0);
    else if (keycode == S_KEY)
        move_player(game, 0, 1);
    else if (keycode == D_KEY)
        move_player(game, 1, 0);

    return (0);
}
