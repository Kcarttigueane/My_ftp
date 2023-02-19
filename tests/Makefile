##
## EPITECH PROJECT, 2023
## STEP-1
## File description:
## Makefile
##

CC	=	gcc

RM	=	rm -f

TARGET	=	unit-tests

SRCS	=	$(wildcard *.c) \
			$(wildcard ../lib/*.c) \
			$(wildcard ../src/*.c) \

SRCS	:=	$(filter-out ../main.c, $(SRCS))


OBJS	=	$(SRCS:.c=.o)


CFLAGS	=	--coverage -Wall -Wextra -I ../include

all	:	$(TARGET)
		./$(TARGET)

$(TARGET)	:	$(OBJS)
				$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) -lcriterion

clean:
	$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(TARGET)
			$(RM) $(wildcard ../lib/*.gcno)
			$(RM) $(wildcard ../lib/*.gcda)
			$(RM) $(wildcard ../src/*.gcno)
			$(RM) $(wildcard ../src/*.gcda)
			$(RM) $(wildcard *.gcno)
			$(RM) $(wildcard *.gcda)

re	:	fclean all

.PHONY: all clean fclean re
