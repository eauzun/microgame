#include "../includes/so_long.h"

void	init_images(t_game *game, int *width, int *height)
{
	game->player_down_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/player_down.xpm", width, height);
	game->player_up_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/player_up.xpm", width, height);
	game->player_left_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/player_left.xpm", width, height);
	game->player_right_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/player_right.xpm", width, height);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/wall.xpm", width, height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/floor.xpm", width, height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/exit.xpm", width, height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, 
		"textures/collectible.xpm", width, height);
}

int	check_image_load(t_game *game)
{
	if (!game->player_down_img || !game->player_up_img || 
		!game->player_left_img || !game->player_right_img ||
		!game->wall_img || !game->floor_img || 
		!game->exit_img || !game->collectible_img)
	{
		print_error("Failed to load game textures");
		return (0);
	}
	return (1);
}

void	game_init(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("MLX initialization failed");
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, 
		game->map->width * TILE_SIZE, 
		game->map->height * TILE_SIZE, 
		"So Long");
	if (!game->win)
	{
		print_error("Window creation failed");
		exit(1);
	}
	width = TILE_SIZE;
	height = TILE_SIZE;
	init_images(game, &width, &height);
	if (!check_image_load(game))
		exit(1);
	game->player_direction = PLAYER_DOWN;
	game->player_current_img = game->player_down_img;
	game->moves = 0;
}

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
}
