# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 16:24:14 by jngerng           #+#    #+#              #
#    Updated: 2023/05/29 16:24:14 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJ_DIR = obj
LIB_NAME = isalpha isdigit isalnum isascii isprint toupper tolower strchr strrchr \
		strlen strncmp strlcpy strlcat strnstr atoi bzero memcpy memmove memset memchr \
		memcmp calloc strdup substr strjoin strtrim split itoa strmapi striteri \
		putchar_fd putstr_fd putendl_fd putnbr_fd lstnew lstadd_front lstsize lstlast \
		lstadd_back lstdelone lstclear lstiter lstmap
LIB_SRC = $(foreach file, $(LIB_NAME), libft/ft_$(file).c)
LIB_OBJ = $(foreach file, $(LIB_NAME), $(OBJ_DIR)/ft_$(file).o)
GNL_NAME = get_next_line get_next_line_utils
GNL_SRC = $(foreach file, $(GNL_NAME), gnl/$(file).c)
GNL_OBJ = $(foreach file, $(GNL_NAME), $(OBJ_DIR)/$(file).o)
INC = -I includes
CFLAGS = -Wall -Wextra -Werror
CC = gcc

$(OBJ_DIR)/%.o: gnl/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: libft/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(LIB_OBJ) $(GNL_OBJ)
	ar rc $(NAME) $(LIB_OBJ) $(GNL_OBJ)

all : $(NAME)

clean:
	rm -f $(LIB_OBJ) $(GNL_OBJ)
	if [ $(OBJ_DIR) != "." ]; then \
		if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi \
	fi

fclean: clean
	rm -f $(NAME)

re: fclean all

