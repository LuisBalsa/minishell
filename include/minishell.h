/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:04:57 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/10 12:33:15 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ncurses.h>
# include <term.h>

# define PROMPT_BEGIN "\033[97m┎─── \033[4m\033[1m\033[96m"
# define PROMPT_END "\n\033[0m\033[97m┖─❯ \033[0m"

# define STOP 0
# define CONTINUE 1
# define RESTORE 2

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define BLOCK 4
# define AND 5
# define OR 6

# define MAXARGS 20

# define SPACES " \t\n\v\f\r"

# define ERROR_TITLE "minishell: "
# define ERROR_QUOTE "unclosed quotes"
# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_REDIR "syntax error near unexpected token `newline'"
# define ERROR_SINTAX "syntax error"

extern int	g_exit;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	int	type;
}		t_cmd;

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}		t_exec;

typedef struct s_redir
{
	int		type;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}		t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}		t_pipe;

typedef struct s_block
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}		t_block;

typedef struct s_and
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}		t_and;

typedef struct s_or
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}		t_or;

typedef struct s_shell
{
	char	*line;
	char	*prompt;
	char	*ps;
	char	*es;
	t_env	*env;
	t_cmd	*cmd;
	int		status;
}		t_shell;

t_env	*add_env(t_env *env, char *key, char *value);
void	envp_to_list(char **envp, t_env **env);
void	envp_destroy(t_env *env);
char	*get_env(char *key, t_shell *shell);

void	sig_handler(int sig);

void	print_error(char *msg, int status, int exit, t_shell *shell);

void	expand_line(t_shell *shell);

#endif
