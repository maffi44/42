NAME = fractol

SRC =   main.c error.c hooks.c color_loop_helper_1.c color_loop.c \
        opencl.c

INCL = header.h

GCC_FLAGS = #-Wall -Werror -Wextra

MLX_LIB = MinilibX/minilibx_macos/libmlx.a
MLX_DIR = MinilibX/minilibx_macos/

FT_LIB = libft/libft.a
FT_DIR = libft/

FRAMEWORKS = -framework OpenGL -framework AppKit -framework OpenCL

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(MLX_LIB) $(FT_LIB) $(NAME)

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