#include "../includes/so_long.h"

int	check_file_extension(char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	if (len < 4)
		return (-1);
	if (file_path[len - 4] != '.' ||
		file_path[len - 3] != 'b' ||
		file_path[len - 2] != 'e' ||
		file_path[len - 1] != 'r')
		return (-1);
	return (0);
}

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

int	check_arguments(int argc)
{
	if (argc != 2)
	{
		print_error("Invalid number of arguments");
		return (1);
	}
	return (0);
}

int	check_map_file(char *file_path)
{
	int	fd;

	if (check_file_extension(file_path) == -1)
	{
		print_error("Invalid file extension");
		return (1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		print_error("Cannot open map file");
		return (1);
	}
	close(fd);
	return (0);
}

int	allocate_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		print_error("Memory allocation failed");
		return (1);
	}
	ft_memset(game->map, 0, sizeof(t_map));
	return (0);
}

int	parse_and_validate_map(t_game *game, char *file_path)
{
	if (map_parse(file_path, game->map) == -1 || map_validate(game->map) == -1)
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
	if (check_arguments(argc))
		return (1);
	if (check_map_file(argv[1]))
		return (1);
	if (allocate_map(&game))
		return (1);
	if (parse_and_validate_map(&game, argv[1]))
		return (1);
	game_init(&game);
	game_render(&game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, (void *)exit, 0);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
