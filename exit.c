#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
}

void interrupt(t_game *game)
{

		free_map(game);
		mlx_destroy_image(game->mlx, game->player_down);
		mlx_destroy_image(game->mlx, game->player_up);
		mlx_destroy_image(game->mlx, game->player_left);
		mlx_destroy_image(game->mlx, game->player_right);
		mlx_destroy_image(game->mlx, game->wall);
		mlx_destroy_image(game->mlx, game->floor);
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
		free(game);
		exit(0);
}