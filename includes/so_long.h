/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:30:38 by emuzun            #+#    #+#             */
/*   Updated: 2025/03/21 11:29:37 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 64
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		exit_x;
	int		exit_y;
	int		*visited;
	int		collected;
}	t_map;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*player_down_img;
	void	*player_up_img;
	void	*player_left_img;
	void	*player_right_img;
	void	*wall_img;
	void	*floor_img;
	void	*exit_img;
	void	*collectible_img;
	void	*player_current_img;
	int		player_direction;
	int		moves;
}	t_game;

void	ft_putnbr(int n);
void	free_map(t_map *map);
int		map_parse(char *file_path, t_map *map);
int		map_validate(t_map *map, t_game *game);
int		check_map_rectangular(t_map *map);
int		check_top_bottom_walls(t_map *map);
int		check_side_walls(t_map *map);
int		count_map_elements(t_map *map);
int		check_path(t_map *map);
int		exit_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	game_init(t_game *game);
void	game_render(t_game *game);
void	move_player(t_game *game, int dx, int dy);
void	set_player_image(t_game *game, int dx, int dy);
void	free_game_images(t_game *game);
void	free_game(t_game *game);
void	*ft_memset(void *ptr, int c, size_t num);
int		open_file(char *file_path);
void	close_file(int fd);
void	print_error(char *error_message, t_game *game);
int		check_file_extension(char *file_path);
void	set_exit_position(t_map *map, int x, int y);
void	set_player_position(t_map *map, int x, int y);
int		check_map_walls_and_elements(t_map *map, t_game *game);
int		validate_map_chars(char **map);

#endif