NAME = fdf

SRC = main.c draw_line.c render.c functions.c matrix.c map_parser.c

INCL = *.h

GCC_FLAGS = #-Ofast #-Wall -Werror -Wextra

MLX_LIB = MinilibX/minilibx_macos/libmlx.a

FT_LIB = libft/libft.a
FT_DIR = libft/

FRAMEWORKS = -framework OpenGL -framework AppKit

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(FT_LIB) $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) $(FRAMEWORKS) $(MLX_LIB) $(FT_LIB) -o $(NAME) -I /Users/mcamila/MyProjects/42/42/libft

%.o: %.c ${INCL}
	@gcc $(GCC_FLAGS) -c $<
	@echo compiled $<

$(FT_LIB):
	@$(MAKE) -sC $(FT_DIR)

clean:
	rm -rf $(OBJ)
	@$(MAKE) -sC libft/ clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -sC libft/ fclean

re: fclean all