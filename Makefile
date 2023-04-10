NAME = cub3d

CC = gcc

CFLAGS	= -Wall -Werror -Wextra  -I. -O3 -Ofast -fsanitize=address -I $(MLX) -I $(LIBFT) -g

MLX = mlx

LIBFT = libft

FRAMEWORK = -framework OpenGl -framework AppKit

SRCS = src/utils.c src/render.c src/hooks.c src/parser.c src/color_parser.c \
		src/param_parser.c src/map_parser.c src/map_checks.c src/draw_walls.c \
		src/checks.c src/main.c

OBJS = $(SRCS:.c=.o)


all: lib $(NAME)

lib:
	@make -C $(MLX)
	@make -sC $(LIBFT)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -L $(MLX) -L $(LIBFT) -o $@ $^ -lmlx -lft $(FRAMEWORK)

clean:
	@make -C $(MLX) clean
	@make -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all
