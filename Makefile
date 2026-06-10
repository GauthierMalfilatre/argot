##
## FREE PROJECT, 2026
## ARGOT
## File description:
## Makefile
##
SRC = 	src/

NAME = libargot.a

CC = ar rc
CLFAGS = -Wall -Wextra -O3 -g

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(NAME) $(OBJ) $(CLFAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
