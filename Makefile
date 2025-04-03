NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -L/Users/sabderra/Desktop/MLX42/ -lmlx42 -lglfw3

SRCS = so_long.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_game.c utils1.c utils2.c validation_of_map.c \
		delete_get_funs.c free.c graphic_tools.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
