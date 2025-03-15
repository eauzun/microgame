#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

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
    void *mlx;
    void *win;
    t_map *map;
    void *player_img;
    void *wall_img;
    void *floor_img;
    void *exit_img;
    void *collectible_img;
    int moves;
} t_game;

// Get Next Line fonksiyon prototipleri
char *get_all_line(int fd, char *all_line);
char *till_nl(char *all_line);
char *return_rest(char *all_line);
char *get_next_line(int fd);
char *ft_strjoin(char *s1, char *s2);
size_t  ft_strnl(char *s);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

// Harita işleme fonksiyonları
int     map_parse(char *file_path, t_map *map);
int     map_validate(t_map *map);

// Oyun yönetimi fonksiyonları
void    game_init(t_game *game);
void    game_render(t_game *game);
int     handle_keypress(int keycode, t_game *game);
void    move_player(t_game *game, int dx, int dy);

// Bellek yönetimi fonksiyonları
void    free_map(t_map *map);
void    free_game(t_game *game);

// Yardımcı fonksiyonlar
void	ft_putnbr(int n);
size_t	ft_strlen(const char *s);
void    print_error(char *message);
int     check_file_extension(char *file_path);

#endif