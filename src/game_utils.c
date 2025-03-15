#include "../includes/so_long.h"

void free_map(t_map *map)
{
    int i;

    if (!map)
        return;

    if (map->grid)
    {
        for (i = 0; map->grid[i]; i++)
            free(map->grid[i]);
        free(map->grid);
    }
    free(map);
}

void free_game(t_game *game)
{
    if (game->player_img)
        mlx_destroy_image(game->mlx, game->player_img);
    if (game->wall_img)
        mlx_destroy_image(game->mlx, game->wall_img);
    if (game->floor_img)
        mlx_destroy_image(game->mlx, game->floor_img);
    if (game->exit_img)
        mlx_destroy_image(game->mlx, game->exit_img);
    if(game->collectible_img)
        mlx_destroy_image(game->mlx, game->collectible_img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);

    free_map(game->map);
    free(game->mlx);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}
