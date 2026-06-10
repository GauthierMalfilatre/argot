##
## FREE PROJECT, 2026
## ARGOT
## File description:
## Makefile
##

SRC =   src/argot_add_arg.c \
        src/argot_parse.c \
        src/argot_get.c \
		src/argot_clear.c \

OBJ =   $(SRC:.c=.o)

NAME =  libargot.a

CC =    gcc
AR =    ar rc

CFLAGS += -Wall -Wextra -O3 -g
CPPFLAGS += -Iinclude/

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
