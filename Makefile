MAKEFLAGS += -s
NAME				= cub3D
LIBFT				= ./inc/libft/libft.a
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/
CC					= cc
SANITIZE_FALGS		= -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer
CFLAGS				= -Wall -Werror -Wextra -g3 -I$(INC)
RM					= rm -rf
SRCS				= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#===================================================================================| Colors |

RED					= "\033[31m"
GREEN				= "\033[32m"
ORANGE				= "\033[38;5;208m"
PURPLE				= "\033[35m"
YELLOW				= "\033[33m"
CYAN				= "\033[36m"
RESET				= "\033[0m"

#===================================================================================| Commands |

all:				$(NAME)

$(NAME): 			$(OBJS) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@printf "🔧 Compiling %s %b[OK]%b\n" "$<" "$(GREEN)" "$(RESET)"
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
					@make -C ./inc/libft/

clean:
					@$(RM) $(OBJ_DIR)
					@make clean -C ./inc/libft/
					@clear
					@echo " "
					@echo " "
					@echo "🗑️ - Program has been cleaned!"
					@echo " "
					@echo " "
					@sleep 1
					@clear

fclean: 			clean
					@$(RM) $(NAME)

re: 				fclean all

norm:
					norminette -R CheckForbiddenSourceHeader

val:				
					clear
						valgrind --leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes \
						--suppressions=readline_supressor ./$(NAME)