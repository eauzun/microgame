/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:30:01 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/19 19:40:20 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	can_move(t_game *game, int new_x, int new_y)
{
	if (game->map->grid[new_y][new_x] == '1')
		return (0);
	if (game->map->grid[new_y][new_x] == 'E')
	{
		if (game->map->collectibles > 0)
			return (0);
		write(1, "Congratulations! You won!\n", 26);
		free_game(game);
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
		write(1, "Collectibles left: ", 19);
		ft_putnbr(game->map->collectibles);
		write(1, "\n", 1);
	}
}

void	set_player_image(t_game *game, int dx, int dy)
{
	if (dx > 0)
		game->player_current_img = game->player_right_img;
	else if (dx < 0)
		game->player_current_img = game->player_left_img;
	else if (dy > 0)
		game->player_current_img = game->player_down_img;
	else if (dy < 0)
		game->player_current_img = game->player_up_img;
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map->player_x + dx;
	new_y = game->map->player_y + dy;
	set_player_image(game, dx, dy);
	if (!can_move(game, new_x, new_y))
		return ;
	collect_item(game, new_x, new_y);
	game->map->grid[game->map->player_y][game->map->player_x] = '0';
	game->map->grid[new_y][new_x] = 'P';
	game->map->player_x = new_x;
	game->map->player_y = new_y;
	game->moves++;
	write(1, "Moves: ", 7);
	ft_putnbr(game->moves);
	write(1, "\n", 1);
	game_render(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_game(game);
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
