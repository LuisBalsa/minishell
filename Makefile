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
_SUBFOLDERS	= built-ins envp error_frees line parser run_cmd expand
VPATH		= $(SRCS) $(addprefix $(SRCS)/, $(_SUBFOLDERS)) bonus/$(SRCS) $(addprefix bonus/$(SRCS)/, $(_SUBFOLDERS))
OBJ_DIR		= bin
#OBJ_DIR_BONUS	= objs_bonus

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FILES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
NAME		= minishell
RULE 		= .all
RULE_BONUS 	= .bonus
_FILES		= main envp signals init_line parser expand_arg expand_utils expand_wildcard trim \
			parseline here_doc nodes_constructors nodes_constructors2 \
			free_cmd free_cmd2 error_free run_cmd run_cmd2 run_cmd3 \
			run_builtin pwd echo export cd unset env exit env_utils chdir checks
_FILES_BONUS= $(_FILES:%=%_bonus)
OBJS		= $(_FILES:%=%.o)
OBJS_BONUS	= $(_FILES_BONUS:%=%.o)
TARGET		= $(addprefix $(OBJ_DIR)/, $(OBJS))
TARGET_BONUS= $(addprefix $(OBJ_DIR)/, $(OBJS_BONUS))


#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ RULES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
all: $(NAME)

$(NAME): $(RULE) $(OBJ_DIR) $(TARGET)
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)libft/*$(RESET)"
	$(MAKE) $(MK) -C $(LIBFT_PATH)

	echo "[$(CYAN) Linking $(RESET)] $(GREEN)*$(RESET)"
	$(CC) $(CFLAGS) $(TARGET) -o $(NAME) -I $(DEPS) -lreadline $(LIBFT)

	echo "$(GREEN)Done.$(RESET)"

${RULE}:
	touch ${RULE}
	${RM} ${RULE_BONUS}

bonus: ${RULE_BONUS}

${RULE_BONUS}: $(OBJ_DIR) ${TARGET_BONUS}
	touch ${RULE_BONUS}
	${RM} ${RULE}
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)libft/*$(RESET)"
	$(MAKE) $(MK) -C $(LIBFT_PATH)

	echo "[$(CYAN) Linking $(RESET)] $(GREEN)*$(RESET)"
	$(CC) $(CFLAGS) $(TARGET_BONUS) -o $(NAME) -I $(DEPS) -lreadline $(LIBFT)

	echo "$(GREEN)Done.$(RESET)"

$(OBJ_DIR)/%.o : %.c
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DEPS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) clean $(MK) -C $(LIBFT_PATH)

	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(OBJ_DIR)$(RESET)"
	$(RM) $(OBJ_DIR) ${RULE} ${RULE_BONUS} output.log readline.supp

fclean: clean
	$(MAKE) fclean $(MK) -C $(LIBFT_PATH)

	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(NAME)$(RESET)"
	$(RM) $(NAME)

re: fclean all

run:
	clear
	./minishell

r: re run

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --log-file=output.log ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

.SILENT:

.PHONY: libft all bonus clean fclean re run r leaks
