# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 22:59:32 by jgarcia           #+#    #+#              #
#    Updated: 2023/02/06 00:48:51 by jgarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minilisp
CC = gcc
CFLAGS = -Wall -Wextra -g
LINK = -lreadline -Lgnl -lgnl
RM = rm -f
SRCDIR = src
OBJDIR = obj
BIN = bin
SRC = main.c mpc.c eval.c
OBJ = $(SRC:.c=.o)
SOURCE = $(addprefix $(SRCDIR)/,$(SRC))
OBJECT = $(addprefix $(OBJDIR)/,$(OBJ))
GNLDIR = gnl
GNL = gnl/libgnl.a

all : $(BIN)/$(NAME)

$(BIN)/$(NAME): $(OBJECT) $(GNL)
	@echo "===========>LINKING <============="
	@mkdir -p $(BIN)
	$(CC) $(OBJECT) $(LINK) -o $(BIN)/$(NAME)

$(GNL):
	make -C gnl

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "=======>COMPILE $< <========"
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJECT)

fclean : clean
	@$(RM) $(BIN)/$(NAME)

re : fclean $(BIN)/$(NAME)

.PHONY: all re clean fclean