NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  error_checks.c

OBJ = $(SRC: .c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) 

fclean: 
	  rm $(NAME)

.PHONY: all clean fclean re