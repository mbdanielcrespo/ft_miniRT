NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build

# COLORS #
GREEN = "\033[0;32m"
WHITE = "\033[0m"

# LIBFT #
LIBFT_DIR = libft
LIBFT = libft/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MINILIBX #
MLX_DIR = .minilibx-linux 
MLX = .minilibx-linux/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

INC_FLAGS = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)/inc

SRC_FILES = main.c \
			calculus/vector_math.c calculus/lights.c \
			utils/validate.c utils/mlx_setup.c utils/utils.c utils/utils2.c \
			parsing/data.c parsing/parser.c parsing/sphere.c parsing/plane.c parsing/cylinder.c \
			viewport.c \
			cleanup/cleanup1.c \
			intersections/sp_intersection.c intersections/pl_intersection.c intersections/cy_intersection.c \
			intersections/obj_intersection.c intersections/intersection.c \
			debug.c 

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	@echo "Compiling $@"
	@$(CC) $(OBJS) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_FLAGS) $(INC_FLAGS) -o $@
	@echo $(GREEN)"Done!"$(WHITE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
