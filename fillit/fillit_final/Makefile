# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 14:22:48 by mcamila           #+#    #+#              #
#    Updated: 2019/11/11 22:43:46 by bjasper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = validity.c validity1.c fillit_2.c fillit_22.c

INCL = fillit.h

GCC_FLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o fillit

%.o: %.c ${INCL}
	gcc $(GCC_FLAGS) -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
