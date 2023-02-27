##
## EPITECH PROJECT, 2023
## STEP-1
## File description:
## Makefile
##

CC ?=gcc

RM	= rm -f

NAME	= myftp

SRC	=	$(wildcard *.c)	\
		$(wildcard lib/*.c) \
		$(wildcard src/**/*.c) \
		$(wildcard src/**/**/*.c)\
 		$(wildcard src/*.c) \


OBJ	= $(SRC:.c=.o)

CFLAGS	+= -Wall -Wextra -I ./include -g3

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(wildcard vgcore*)
	make -C tests fclean

re:	fclean all

tests_run:
	make -C tests all

.PHONY: all clean fclean re tests_run
