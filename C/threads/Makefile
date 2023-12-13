NAME = philo
CC = gcc
CFLAGS = -pthread -fsanitize=thread -g

SRC = a.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)