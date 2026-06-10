##
## FREE PROJECT, 2026
## ARGOT
## File description:
## Makefile
##
SRC = 	src/argot_add_arg.c \
		src/argot_parse.c \
		src/argot_get.c \

NAME = libargot.a

CC = ar rc
CLFAGS += -Wall -Wextra -O3 -g
LDFLAGS += -Iinclude/

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
