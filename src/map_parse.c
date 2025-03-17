#include "../includes/so_long.h"

static int	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

static int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

static void	close_file(int fd)
{
	if (fd != -1)
		close(fd);
}

static int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open_file(file_path);
	if (fd == -1)
		return (-1);

	while ((line = get_next_line(fd)) != NULL)
	{
		lines++;
		free(line);
	}
	close_file(fd);
	return (lines);
}

static int	read_map_lines(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		remove_newline(line);
		map->grid[i] = line;
		i++;
	}
	map->grid[i] = NULL;
	return (0);
}

int	map_parse(char *file_path, t_map *map)
{
	int		fd;

	map->height = count_lines(file_path);
	if (map->height <= 0)
		return (-1);

	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (-1);

	fd = open_file(file_path);
	if (fd == -1)
	{
		free(map->grid);
		return (-1);
	}

	if (read_map_lines(fd, map) == -1)
	{
		free(map->grid);
		close_file(fd);
		return (-1);
	}

	map->width = ft_strlen(map->grid[0]);
	close_file(fd);
	return (0);
}
