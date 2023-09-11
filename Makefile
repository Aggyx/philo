# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 16:01:49 by smagniny          #+#    #+#              #
#    Updated: 2023/09/11 21:44:58 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -Wall -Werror -Wextra

SRC = main.c src/brain.c src/death_handler.c src/error_handler.c \
		src/init.c src/parse_utils.c src/utils.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@

clean:
	@echo "Deleting objects..."
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

