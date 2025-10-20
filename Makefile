NAME = cub3D

MLX = minilibx/libmlx_Linux.a

SRC = main.c get_next_line.c get_next_line_utils.c utils.c parsing.c render.c \
		render_2.c render_3.c texture.c parsing_2.c raycasting.c raycasting_2.c \
		parsing_3.c parsing_4.c helper.c helper_2.c utils_2.c parsing_6.c \
		parsing_7.c texture_2.c parsing_8.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C minilibx
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -lX11 -lXext -lm -o $(NAME)

$(OBJ): %.o: %.c cub3D.h minilibx/mlx.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C minilibx clean 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all