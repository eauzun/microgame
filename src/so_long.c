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

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (argc != 2)
	{
		print_error("Invalid number of arguments");
		return (1);
	}
	if (check_file_extension(argv[1]) == -1)
	{
		print_error("Invalid file extension");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error("Cannot open map file");
		return (1);
	}
	close(fd);
	game.map = malloc(sizeof(t_map));
	if (!game.map)
	{
		print_error("Memory allocation failed");
		return (1);
	}
	if (map_parse(argv[1], game.map) == -1 || map_validate(game.map) == -1)
	{
		free_map(game.map);
		return (1);
	}
    game_init(&game);
	game_render(&game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, (void *)exit, 0);
	mlx_loop(game.mlx);
	return (0);
}
