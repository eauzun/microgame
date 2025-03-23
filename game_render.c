/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:30:03 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/19 20:42:44 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
	else if (element == '0')
		mlx_put_image_to_window(game->mlx, game->win,
			game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
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
			render_element(game, x, y, game->map->grid[y][x]);
			x++;
		}
		y++;
	}
}

void	print_error(char *error_message, t_game *game)
{
	if (error_message)
	{
		write(2, "Error\n", 6);
		write(2, error_message, ft_strlen(error_message));
		write(2, "\n", 1);
	}
	free_game(game);
	exit(1);
}

void	set_player_position(t_map *map, int x, int y)
{
	map->player_x = x;
	map->player_y = y;
}

void	set_exit_position(t_map *map, int x, int y)
{
	map->exit_x = x;
	map->exit_y = y;
}
