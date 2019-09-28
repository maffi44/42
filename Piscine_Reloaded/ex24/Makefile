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

NAME = libft.a

SRC_PATH = ./srcs/

SRC = $(SRC_PATH)ft_putchar.c $(SRC_PATH)ft_putstr.c \
		$(SRC_PATH)ft_strcmp.c $(SRC_PATH)ft_strlen.c \
		$(SRC_PATH)ft_swap.c

INCL_PATH = ./includes/

INCL = $(INCL_PATH)*.h

GCC_FLAGS = -Wall -Werror -Wextra

OBJ = ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o

all: $(NAME)

$(NAME):
	gcc $(GCC_FLAGS) -c $(SRC) -I $(INC) -I-
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
