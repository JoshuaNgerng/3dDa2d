# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 14:22:20 by jngerng           #+#    #+#              #
#    Updated: 2024/05/30 14:03:15 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC_DIR = srcs
UTLIS_DIR = utlis
READ_DIR = read
GAME_DIR = game
OBJ_DIR = obj
F_MAIN = main
F_UTLIS = errmsg free string
F_READ = read elements check buffer
F_GAME = loop ply texture scene map map2 assest \
		 raycast_loop raycast_check draw draw2
SRC_M = $(foreach item, $(F_MAIN), $(SRC_DIR)/$(item).c)
SRC_U = $(foreach item, $(F_UTLIS), $(SRC_DIR)/$(UTLIS_DIR)/$(item).c)
SRC_R = $(foreach item, $(F_READ), $(SRC_DIR)/$(READ_DIR)/$(item).c)
SRC_G = $(foreach item, $(F_GAME), $(SRC_DIR)/$(GAME_DIR)/$(item).c)
SRC = $(SRC_M) $(SRC_U) $(SRC_R) $(SRC_G)
OBJ = $(foreach item, $(F_MAIN) $(F_UTLIS) $(F_READ) $(F_GAME), $(OBJ_DIR)/$(item).o)
INC = -I includes -I lib/includes
LIB = -L lib -lft -lm -lmlx -framework OpenGL -framework AppKit
CC = gcc
CFLAGS = -Wall -Wextra -Werror #$(CMEM)
CMEM = -fsanitize=address -g3

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(UTLIS_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(READ_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(GAME_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@ echo COMPLY LIBFT
	@ $(MAKE) -C lib
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(INC)
	@ echo DONE

all : $(NAME)

$(OBJ_DIR):
	@ mkdir $(OBJ_DIR)
	@ echo START

clean:
	@ echo CLEAN OBJ
	@ rm -f $(OBJ)
	@ if [ $(OBJ_DIR) != "." ]; then \
	 	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi \
	fi

fclean: clean
	@ echo CLEAN LIBFT OBJ
	@ $(MAKE) fclean -C lib
	@ rm -f $(NAME)
	@ echo FINISH CLEAN

re: fclean all
