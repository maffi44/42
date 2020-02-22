NAME = fdf

SRC =   main.c draw_line.c render.c functions.c matrix.c map_parser.c draw_horizontal_line.c\
        error.c hooks.c make_ref_obj.c make_triangles.c initializate_camera.c color_loop.c\
        color_loop_helper_1.c draw_tri_helper.c matrix_2.c

INCL = header.h matrix.h structs.h functions.h map_parser.h

GCC_FLAGS = -Wall -Werror -Wextra

MLX_LIB = MinilibX/minilibx_macos/libmlx.a
MLX_DIR = MinilibX/minilibx_macos/

FT_LIB = libft/libft.a
FT_DIR = libft/

FRAMEWORKS = -framework OpenGL -framework AppKit

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(FT_LIB) $(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) $(FRAMEWORKS) $(MLX_LIB) $(FT_LIB) -o $(NAME)
	@echo compiled $(NAME)

%.o: %.c ${INCL}
	@gcc $(GCC_FLAGS) -c $<
	@echo compiled $<

$(FT_LIB):
	@$(MAKE) -sC $(FT_DIR)

$(MLX_LIB):
	@$(MAKE) -sC $(MLX_DIR)

clean:
	rm -rf $(OBJ)
	@$(MAKE) -sC $(FT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -sC $(FT_DIR) fclean

re: fclean all