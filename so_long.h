#ifndef SO_LONG_H
#define SO_LONG_H

#include "so_long.h"
#include "get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define BUFFER_SIZE 1024
#define TILE_SIZE 64

typedef struct s_game {
    void    *mlx;
    void    *win;
    void    *wall;
    void    *floor;
    void    *collectible;
    void    *exit;
    void    *player_up;
    void    *player_down;
    void    *player_left;
    void    *player_right;
    void    *player;
    char    **map;
    char    **mapcpy;
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
}   t_game;


int key_hook(int keycode, t_game *game);
int left(t_game *game, int new_x);
int right(t_game *game, int new_x);
int up(t_game *game, int new_y);
int down(t_game *game, int new_y);
char	*get_all_line(int fd, char *all_line);
char	*till_nl(char *all_line);
char	*return_rest(char *all_line);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
void    render_map(t_game *game);
void    interrupt(t_game *game);
void	free_map(t_game *game);
size_t	ft_strnl(char *s);
size_t	ft_strlen(const char *s);
t_game  *load_map(char *file);

#endif
