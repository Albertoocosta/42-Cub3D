MAKEFLAGS			+= -s
NAME				= cub3D
TEST_NAME 			= cub3D_test
LIBFT				= ./inc/libft/libft.a
INC					= inc/
SRC_DIR				= src/
MLXFLAGS 			= -lXext -lX11 -lm -lbsd
MLX_DIR				= ./inc/Minilibx
MLX					= $(MLX_DIR)/libmlx.a
OBJ_DIR				= obj/
CC					= cc
SANITIZE_FALGS		= -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer
CFLAGS				= -Wall -Werror -Wextra -g3 -I$(INC)
RM					= rm -rf
SRCS				= $(shell find $(SRC_DIR) -type f -name "*.c")
TEST_SRCS			= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
TEST_OBJS			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(TEST_SRCS))

#===================================================================================| Colors |

RED					= \033[31m
GREEN				= \033[32m
ORANGE				= \033[38;5;208m
PURPLE				= \033[35m
YELLOW				= \033[33m
CYAN				= \033[36m
RESET				= \033[0m

#===================================================================================| Commands |

all:				$(NAME)

$(NAME): 			$(OBJS) $(LIBFT) $(MLX)
					@$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(MLXFLAGS) -o $(NAME)

test: 				$(LIBFT) $(MLX) $(TEST_OBJS)
					@echo "$(YELLOW)Linking $(TEST_NAME)...$(NC)"
					@$(CC) $(CFLAGS) $(TEST_OBJS) $(MLX) $(LIBFT) $(MLXFLAGS) -o $(TEST_NAME)
					@echo "$(GREEN)$(TEST_NAME) created successfully!$(NC)"
					@echo "$(GREEN)Run ./$(TEST_NAME) to test with manual map$(NC)"


$(MLX):
					@cd $(MLX_DIR) && make >/dev/null 2>&1 || make
					@if [ ! -f $(MLX) ]; then \
						echo "❌ MiniLibX library not found at $(MLX)"; \
						exit 1; \
					else \
						echo "✅ MiniLibX built successfully"; \
					fi

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@printf "🔧 Compiling %s ${GREEN}[OK]${RESET}\n" "$<"
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
	@make fclean -C ./inc/libft/
	@make -C ./inc/libft/

clean:
					@$(RM) $(OBJ_DIR)
					@make clean -C ./inc/libft/
					@make clean -C $(MLX_DIR)
#					@clear
					@echo " "
					@echo " "
					@echo "🗑️ - Program has been cleaned!"
					@echo " "
					@echo " "
					@sleep 1
#					@clear

fclean: 			clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@make clean -C $(MLX_DIR)

re: 				fclean all

norm:
					norminette -R CheckForbiddenSourceHeader

val:				
					clear
						valgrind --leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes ./cub3D debug.cub
