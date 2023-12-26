
NAME	= philo
SRC		= die.c init.c parser.c philosophers.c duration.c time.c utilities.c leak.c
OBJ		= die.o init.o parser.o philosophers.o duration.o time.o utilities.o leak.o
LIB		= -lpthread
CC 		= gcc -g
CFLAGS 	= -Wall -Wextra -Werror -fsanitize=thread -pthread
ARCH	= philosophers.dSYM
RM		= rm -rf

$(NAME):	$(OBJ)
			$(CC) ${CFLAGS} -o ${NAME} ${OBJ} ${LIB}

all: 		$(NAME)

clean:
			$(RM) $(OBJ) $(ARCH)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

rxxx:

.PHONY:		all clean fclean re
