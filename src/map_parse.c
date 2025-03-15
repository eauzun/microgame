#include "so_long.h"

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

static int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);

	while ((line = get_next_line(fd)) != NULL)
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

int	map_parse(char *file_path, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	map->height = count_lines(file_path);
	if (map->height <= 0)
		return (-1);

	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (-1);

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		remove_newline(line);
		map->grid[i] = line;
		i++;
	}
	map->grid[i] = NULL;
	close(fd);

	return (0);
}