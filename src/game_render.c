#include "../includes/so_long.h"

static void	render_floor(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, 
		game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_element(t_game *game, int x, int y, char element)
{
	if (element == '1')
		mlx_put_image_to_window(game->mlx, game->win, 
			game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (element == 'C')
		mlx_put_image_to_window(game->mlx, game->win, 
			game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (element == 'P')
		mlx_put_image_to_window(game->mlx, game->win, 
			game->player_current_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (element == 'E')
		mlx_put_image_to_window(game->mlx, game->win, 
			game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
}

void	game_render(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			render_floor(game, x, y);
			render_element(game, x, y, game->map->grid[y][x]);
			x++;
		}
		y++;
	}
}
