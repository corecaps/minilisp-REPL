CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libgnl.a
BONUS_NAME = libft_get_next_line_bonus.a
SOURCES = get_next_line.c get_next_line_utils.c
BONUS_SOURCES = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJ = $(SOURCES:.c=.o)
BONUS_OBJ = $(BONUS_SOURCES:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	ar -rcs $(NAME) $(BONUS_OBJ)

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean:	clean
	rm -f $(NAME)

re : fclean all

.PHONY:	all clean fclean re
