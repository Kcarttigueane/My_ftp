##
## EPITECH PROJECT, 2023
## client
## File description:
## Makefile
##

CC ?=gcc
RM = rm -f

NAME = client
SRCS = $(wildcard *.c) \
       $(wildcard lib/*.c) \
       $(wildcard src/*.c) \

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -Wall -Wextra -I include -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	make -C tests fclean


fclean: clean
	$(RM) $(NAME)
	$(RM) $(wildcard vgcore*)

re: fclean all

tests_run:
	make -C tests all


.PHONY: all clean fclean re tests_run
