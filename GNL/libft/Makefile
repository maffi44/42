# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 14:22:48 by mcamila           #+#    #+#              #
#    Updated: 2019/10/12 21:37:48 by mcamila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_atoi.c       ft_isdigit.c    ft_lstdelone.c  ft_memccpy.c    ft_memdup.c     ft_putendl.c\
		ft_putstr_fd.c  ft_strcpy.c     ft_striteri.c   ft_strmapi.c    ft_strnew.c     ft_strsub.c\
      	ft_bzero.c      ft_isprint.c    ft_lstiter.c    ft_memchr.c     ft_memmove.c    ft_putendl_fd.c\
      	ft_strcat.c     ft_strdel.c     ft_strjoin.c    ft_strncat.c    ft_strnstr.c    ft_strtrim.c\
      	ft_isalnum.c    ft_itoa.c       ft_lstmap.c     ft_memcmp.c     ft_memset.c     ft_putnbr.c\
      	ft_strchr.c     ft_strdup.c     ft_strlcat.c    ft_strncmp.c    ft_strrchr.c    ft_tolower.c\
      	ft_isalpha.c    ft_lstadd.c     ft_lstnew.c     ft_memcpy.c     ft_putchar.c    ft_putnbr_fd.c\
      	ft_strclr.c     ft_strequ.c     ft_strlen.c     ft_strncpy.c    ft_strsplit.c   ft_toupper.c\
      	ft_isascii.c    ft_lstdel.c     ft_memalloc.c   ft_memdel.c     ft_putchar_fd.c ft_putstr.c\
      	ft_strcmp.c     ft_striter.c    ft_strmap.c     ft_strnequ.c    ft_strstr.c

INCL = libft.h

GCC_FLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%c%o:
	gcc $(GCC_FLAGS) -c $< -I $(INC) -I-mak

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all