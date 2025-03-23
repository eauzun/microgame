/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:30:18 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/21 10:31:03 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_arguments(int argc, t_game *game)
{
	if (argc != 2)
	{
		print_error("Invalid number of arguments", game);
		return (1);
	}
	return (0);
}

static int	check_map_file(char *file_path, t_game *game)
{
	int	fd;

	if (check_file_extension(file_path) == -1)
	{
		print_error("Invalid file extension", game);
		return (1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		print_error("Cannot open map file", game);
		return (1);
	}
	close(fd);
	return (0);
}

static int	allocate_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		print_error("Memory allocation failed", game);
		return (1);
	}
	ft_memset(game->map, 0, sizeof(t_map));
	return (0);
}

static int	parse_and_validate_map(t_game *game, char *file_path)
{
	if (map_parse(file_path, game->map) == -1
		|| map_validate(game->map, game) == -1)
	{
		free_map(game->map);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (check_arguments(argc, &game))
		return (1);
	if (check_map_file(argv[1], &game))
		return (1);
	if (allocate_map(&game))
		return (1);
	if (parse_and_validate_map(&game, argv[1]))
		return (1);
	game_init(&game);
	game_render(&game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
