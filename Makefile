NAME := so_long

CC := cc


SOURCE := so_long.c get_next_line.c get_next_line_utils.c key_activity.c exit.c process.c
LIBRARY := -Lminilibx-linux -lmlx -lX11 -lXext -lm
MINILIBX := minilibx-linux/
PRINTF := printf/libftprintf.a

all:
	make -C $(MINILIBX)

	$(CC)  $(SOURCE)  $(LIBRARY)  -o $(NAME) -g

clean:
		make clean -C printf
		make clean -C $(MINILIBX)

fclean: clean
		make clean -C $(MINILIBX)
		make fclean -C printf
		rm -rf $(NAME)