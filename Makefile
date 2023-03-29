NAME = cub3d

CC = gcc

CFLAGS	= -I $(MLX) -I $(LIBFT) -g

MLX = mlx

LIBFT = libft

FRAMEWORK = -framework OpenGl -framework AppKit

SRCS = utils.c render.c hooks.c parser.c color_parser.c \
		param_parser.c map_parser.c map_checks.c draw_walls.c main.c

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
