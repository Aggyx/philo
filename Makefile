# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 16:01:49 by smagniny          #+#    #+#              #
#    Updated: 2023/09/24 23:42:08 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -Wall -Werror -Wextra #-fsanitize=thread -g3

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


