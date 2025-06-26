NAME = cub3D

MLX = minilibx/libmlx_Linux.a

SRC = main.c get_next_line.c get_next_line_utils.c utils.c parsing.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C minilibx
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -lX11 -lXext -o $(NAME)

$(OBJ): %.o: %.c cub3D.h minilibx/mlx.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C minilibx clean 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all