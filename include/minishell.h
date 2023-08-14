/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:04:57 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/14 19:00:01 by luide-so         ###   ########.fr       */
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

# define EXEC 300
# define REDIR 301
# define PIPE 302
# define AND 303
# define HERE_DOC 304
# define OR_OP 305
# define APPEND 306

# define MAXARGS 20

# define SPACES " \t\n\v\f\r"
# define OPERATORS "|><&()"
# define TILDE_EXP "|><&();/ \t\n\v\f\r"

# define ERROR_TITLE "minishell: "
# define ERROR_QUOTE "unclosed quotes"
# define ERROR_SINTAX "syntax error"

extern int	g_exit;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				visible;
	int				index;
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
}		t_exec;

typedef struct s_redir
{
	int		type;
	char	*file;
	int		mode;
	int		fd;
}		t_redir;

typedef struct s_here
{
	int		type;
	char	*eof;
	int		mode;
	int		fd;
}		t_here;

typedef struct s_lr
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}		t_lr;

typedef struct s_shell
{
	char	*line;
	char	*prompt;
	char	*ps;
	char	*es;
	int		line_len;
	t_env	*env;
	t_cmd	*cmd;
	int		status;
	int		envp_size;
}		t_shell;

t_env	*add_env(t_shell *shell, char *key, char *value);
void	envp_to_list(char **envp, t_shell *shell);
void	envp_destroy(t_env *env);
char	*get_env(char *key, t_shell *shell);

void	sig_handler(int sig);
void	pipe_continuation_signal(int sig);

int		print_error(t_shell *shell, char *msg, int exit);
int		print_error_syntax(t_shell *shell, char *msg, int exit);

int		init_line(t_shell *shell);
int		expand_line(t_shell *shell);
int		expand(char *key, int i, int j, t_shell *shell);
int		expand_free(char *key, int i, int j, t_shell *shell);
void	trim_line(t_shell *shell);

int		parser(t_shell *shell);
int		peek(t_shell *shell, char *op, int mode);
int		gettoken(t_shell *shell, char *token);

t_cmd	*or_cmd(t_cmd *left, t_cmd *right);
t_cmd	*and_cmd(t_cmd *left, t_cmd *right);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*redir_cmd(char *file, int mode, int fd);
t_cmd	*here_cmd(char *eof);
t_cmd	*exec_cmd(void);

#endif
