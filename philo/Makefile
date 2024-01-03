
NAME = philo
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c \
	  error_checks.c \
	  parse.c \
	  data_init.c \
	  dinner.c \
	  utils.c \
	  print.c

OBJ = $(SRC: .c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) 

#don't forget to add fclean and make sure that makefile is correct
re: clean all

clean: 
	  rm $(NAME)

.PHONY: all clean fclean re