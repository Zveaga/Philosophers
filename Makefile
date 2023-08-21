NAME = philo

SRC = \
main.c \
utils.c \
initialize.c \
validate_input.c \
watcher_thread.c \
simulation.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror  -g -fsanitize=thread

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re