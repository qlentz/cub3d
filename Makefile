NAME = cub3d

CC = gcc

CFLAGS	= -I ./mlx 

MLX = mlx

LIBFT = libft

FRAMEWORK = -framework OpenGl -framework AppKit

SRCS = utils.c render.c hooks.c main.c

OBJS = $(SRCS:.c=.o)


all: lib $(NAME)

lib:
	@make -C $(MLX)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -L $(MLX) -o $@ $^ -lmlx $(FRAMEWORK)

clean:
	@make -C $(MLX) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
