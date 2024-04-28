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

NAME = libft.a
LIB_NAME = isalpha isdigit isalnum isascii isprint toupper tolower strchr strrchr \
		strlen strncmp strlcpy strlcat strnstr atoi bzero memcpy memmove memset memchr \
		memcmp calloc strdup substr strjoin strtrim split itoa strmapi striteri \
		putchar_fd putstr_fd putendl_fd putnbr_fd lstnew lstadd_front lstsize lstlast \
		lstadd_back lstdelone lstclear lstiter lstmap
LIB_SRC = $(foreach file, $(LIB_NAME), libft/ft_$(file).c)
LIB_OBJ = $(LIB_SRC:.c=.o)
GNL_NAME = get_next_line get_next_line_utils
GNL_SRC = $(foreach file, $(GNL_NAME), gnl/$(file).c)
GNL_OBJ = $(GNL_SRC:.c=.o)
INC = includes
CFLAGS = -Wall -Wextra -Werror
CC = gcc

.c.o:
	@ $(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INC)

all: $(NAME)
	@ ar rc $(NAME) $(LIB_OBJ) $(GNL_OBJ)

$(NAME): $(LIB_OBJ) $(GNL_OBJ)

clean:
	@ rm -f $(LIB_OBJ) $(GNL_OBJ)

fclean: clean
	@ rm -f $(NAME)

re: clean all
