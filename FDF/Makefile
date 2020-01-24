NAME = fdf

SRC = main.c draw_line.c render.c

INCL = *.h

GCC_FLAGS = #-Wall -Werror -Wextra

MLX_LIB = /Users/mcamila/MyProjects/42/42/MinilibX/minilibx_macos/libmlx.a

FT_LIB = /Users/mcamila/MyProjects/42/42/libft/libft.a

FRAMEWORKS = -framework OpenGL -framework AppKit

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) $(FRAMEWORKS) $(MLX_LIB) $(FT_LIB) -o $(NAME) -I /Users/mcamila/MyProjects/42/42/libft

%.o: %.c ${INCL}
	gcc $(GCC_FLAGS) -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all