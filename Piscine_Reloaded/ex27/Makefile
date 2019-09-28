# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 11:59:34 by mcamila           #+#    #+#              #
#    Updated: 2019/09/10 13:48:09 by mcamila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file

SRC = display_file.c

GCC_FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(GCC_FLAGS) -o $(NAME) $(SRC)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all
