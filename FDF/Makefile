NAME = fdf

SRC = main.c draw_line.c render.c functions.c matrix.c map_parser.c

INCL = *.h

GCC_FLAGS = -O1#-Wall -Werror -Wextra

MLX_LIB = MinilibX/minilibx_macos/libmlx.a

FT_LIB = libft/libft.a

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