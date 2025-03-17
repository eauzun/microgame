#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define TILE_SIZE 64
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307

# define PLAYER_DOWN 0
# define PLAYER_UP 1
# define PLAYER_LEFT 2
# define PLAYER_RIGHT 3

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map {
    char **grid;
    int width;
    int height;
    int player_x;
    int player_y;
    int collectibles;
    int exit_x;
    int exit_y;
} t_map;

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_map   *map;
    void    *player_down_img;
    void    *player_up_img;
    void    *player_left_img;
    void    *player_right_img;
    void    *wall_img;
    void    *floor_img;
    void    *exit_img;
    void    *collectible_img;
    void    *player_current_img;
    int     player_direction;
    int     moves;
} t_game;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_putnbr(int n);
void	print_error(char *message);
void	free_map(t_map *map);
int	map_parse(char *file_path, t_map *map);
int	map_validate(t_map *map);
int	check_map_rectangular(t_map *map);
int	check_top_bottom_walls(t_map *map);
int	check_side_walls(t_map *map);
int	count_map_elements(t_map *map);
int	check_path(t_map *map);
int exit_game(t_game *game);
int	handle_keypress(int keycode, t_game *game);
void	game_init(t_game *game);
void	game_render(t_game *game);
void	move_player(t_game *game, int dx, int dy);
void	set_player_image(t_game *game, int dx, int dy);
void	free_game_images(t_game *game);
void	free_game(t_game *game);
char *get_all_line(int fd, char *all_line);
char *till_nl(char *all_line);
char *return_rest(char *all_line);
char *get_next_line(int fd);
char *ft_strjoin(char *s1, char *s2);
size_t  ft_strnl(char *s);

#endif