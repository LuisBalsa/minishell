#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COLORS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COMMANDS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CC = cc
RM = rm -rf
AR = ar -rcs

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FLAGS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address
MK		= --no-print-directory
LIBFT	= -L ./Libft_obj -lft

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FOLDERS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
DEPS		= inc
SRCS		= src
#SRCS_BONUS	= srcs_bonus
LIBFT_PATH	= Libft
_SUBFOLDERS	= built-ins
VPATH		= $(SRCS) $(addprefix $(SRCS)/, $(_SUBFOLDERS))
OBJ_DIR		= bin
#OBJ_DIR_BONUS	= objs_bonus

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FILES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
NAME		= minishell
_FILES		= main envp signals init_line expand_line expand_wildcard expand trim_line parser \
			parseline here_doc nodes_constructors nodes_constructors2 \
			free_cmd free_cmd2 error_free run_cmd run_cmd2 run_cmd3 \
			run_builtin pwd echo export cd unset env exit
OBJS		= $(_FILES:%=%.o)
TARGET		= $(addprefix $(OBJ_DIR)/, $(OBJS))


#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ RULES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
all: $(NAME)

$(NAME): $(OBJ_DIR) $(TARGET)
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)libft/*$(RESET)"
	$(MAKE) $(MK) -C $(LIBFT_PATH)

	echo "[$(CYAN) Linking $(RESET)] $(GREEN)*$(RESET)"
	$(CC) $(CFLAGS) $(TARGET) -o $(NAME) -I $(DEPS) -lreadline $(LIBFT)

	echo "$(GREEN)Done.$(RESET)"

$(OBJ_DIR)/%.o : %.c
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DEPS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) clean $(MK) -C $(LIBFT_PATH)

	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(OBJ_DIR)$(RESET)"
	$(RM) $(OBJ_DIR) output.log

fclean: clean
	$(MAKE) fclean $(MK) -C $(LIBFT_PATH)

	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(NAME)$(RESET)"
	$(RM) $(NAME)

re: fclean all

run:
	clear
	./minishell

r: re run

leaks:
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --log-file=output.log ./minishell

.SILENT:

.PHONY: libft all bonus clean fclean re run r leaks
