# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 11:02:22 by tburnouf          #+#    #+#              #
#    Updated: 2017/10/05 16:12:09 by tburnouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIBFT = libft.a
FLAGS = -Wall -Werror -Wextra
HEADER = includes/

SRC_DIR = srcs/
OBJ_DIR = objs/

FILES = read_file.c
OBJ = $(addprefix $(OBJ_DIR),$(FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(FILES))

all: $(NAME)

$(NAME):
	mkdir objs
	gcc $(FLAGS) -c $(SRC) -o $(OBJ)
	gcc $(FLAGS) $(LIBFT) $(OBJ) -I $(HEADER) -o $(NAME)

clean:
	/bin/rm -rf objs/

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
