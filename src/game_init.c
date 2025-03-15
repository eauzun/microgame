#include"../includes/so_long.h"
void game_init(t_game *game)

{

    int width, height;


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


    // Resim yükleme kontrolleri

    game->player_img = mlx_xpm_file_to_image(game->mlx, 

        "textures/player.xpm", &width, &height);

    game->wall_img = mlx_xpm_file_to_image(game->mlx, 

        "textures/wall.xpm", &width, &height);

    game->floor_img = mlx_xpm_file_to_image(game->mlx, 

        "textures/floor.xpm", &width, &height);

    game->exit_img = mlx_xpm_file_to_image(game->mlx, 

        "textures/exit.xpm", &width, &height);

    game->collectible_img = mlx_xpm_file_to_image(game->mlx, 

        "textures/collectible.xpm", &width, &height);


    // Resim yükleme kontrolleri

    if (!game->player_img || !game->wall_img || !game->floor_img || 

        !game->exit_img || !game->collectible_img)

    {

        print_error("Failed to load game textures");

        exit(1);

    }


    game->moves = 0;

}