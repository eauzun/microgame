NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm


SRC_DIR = src

INC_DIR = includes

OBJ_DIR = obj


SRCS = $(SRC_DIR)/so_long.c \
       $(SRC_DIR)/map_parse.c \
       $(SRC_DIR)/map_validate.c \
       $(SRC_DIR)/game_init.c \
       $(SRC_DIR)/game_render.c \
       $(SRC_DIR)/game_move.c \
       $(SRC_DIR)/game_utils.c \
       $(SRC_DIR)/get_next_line.c \
       $(SRC_DIR)/get_next_line_utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
clean:
	rm -rf $(OBJ_DIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re