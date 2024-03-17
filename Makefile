NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
MLX = minilibx-linux/libmlx.a
MLX_FLAGS = -Lminilibx-linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INC_FLAGS = -I $(INC_DIR)

SRC_FILES = main.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(NAME) : $(OBJS)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(INC_FLAGS) $(MLX) $(MLX_FLAGS)
	@echo "Done!"

$(MLX):
	make -C .minilibx-linux

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@ $(MLX) $(MLX_FLAGS)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re