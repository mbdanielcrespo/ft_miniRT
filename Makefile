NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
LIBFT_DIR = libft
MLX = minilibx-linux/libmlx.a
MLX_FLAGS = -Lminilibx-linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INC_FLAGS = -I $(INC_DIR) -I minilibx-linux -I libft/inc

SRC_FILES = main.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(INC_FLAGS)
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re