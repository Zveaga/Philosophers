NAME = philo

SRC = \
main.c \
utils_1.c \
utils_2.c \
initialize.c \
validate_input.c \
watcher_thread.c \
simulation.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g -pthread

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