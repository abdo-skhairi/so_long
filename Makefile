NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lmlx42 -lm -lX11 -lXext -pthread -lglfw

SRCS = so_long.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_game.c
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
