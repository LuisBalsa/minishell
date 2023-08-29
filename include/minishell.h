/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:04:57 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/29 16:51:56 by luide-so         ###   ########.fr       */
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
/*# include <linux/limits.h>*/
# include <limits.h>
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
# define BLOCK 307

# define MAXARGS 50

# define SPACES " \t\n\v\f\r"
# define OPERATORS "|><&()"
# define TILDE_EXP "|><&();/ \t\n\v\f\r"
# define OP_AND_SP "|><&(); \t\n\v\f\r"

# define ERROR_TITLE "minishell: "
# define ERROR_QUOTE "unclosed quotes"
# define ERROR_SINTAX "syntax error"
# define ERROR_HERE_DOC "unexpected EOF while looking for matching `"

# define SIGRESTORE 1
# define SIGHEREDOC 2
# define SIGCHILD 3
# define SIGIGNORE 4

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
	int		type;
}			t_cmd;

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARGS];
}			t_exec;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}			t_redir;

typedef struct s_here
{
	int		type;
	t_cmd	*cmd;
	char	*eof;
	int		mode;
	int		fdin;
	int		fdout;
}			t_here;

typedef struct s_lrn
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*next;
}			t_lrn;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe;

typedef struct s_block
{
	int		type;
	t_cmd	*block;
}			t_block;

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
	char	**envp;
}			t_shell;

t_env	*add_env(t_shell *shell, char *key, char *value, int visible);
bool	mod_env(t_shell *shell, char *target, char *new_value);
void	export_env(t_shell *shell, char *key, char *value, int visible);
bool	rm_env(char *key, t_shell *shell);
void	envp_to_list(char **envp, t_shell *shell);
void	envp_destroy(t_env *env);
char	*get_env(char *key, t_shell *shell);
void	print_envp(t_shell *shell);
void	update_envp(t_shell *shell);

void	sig_handler(int sig);
void	pipe_continuation_signal(int sig);

void	check(int result, char *msg, int exit);
int		check_fork(void);
int		print_error(t_shell *shell, char *msg, char *msg2, int exit);
int		print_error_syntax(t_shell *shell, char *msg, int exit);
void	free_exit(t_shell *shell);

int		init_line(t_shell *shell);
int		expand_line(t_shell *shell);
int		expand(char *key, int i, int j, char **line);
int		expand_free(char *key, int i, int j, char **line);
void	expand_wildcard(t_shell *shell);
void	trim_line(t_shell *shell);

int		parser(t_shell *shell);
int		peek(t_shell *shell, char *op, int mode);
int		gettoken(t_shell *shell, char **token);
t_cmd	*parseline(t_shell *shell);

void	free_cmd(t_cmd *cmd);
void	free_block(t_block *block);

t_cmd	*or_cmd(t_cmd *left, t_cmd *right, t_cmd *next);
t_cmd	*and_cmd(t_cmd *left, t_cmd *right, t_cmd *next);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd);
t_cmd	*here_cmd(t_cmd *cmd, char *eof);
t_cmd	*exec_cmd(void);
t_cmd	*block_cmd(t_cmd *cmd);

void	run_cmd(t_shell *shell, t_cmd *cmd);
void	run_exec(t_shell *shell, t_exec *cmd);
void	run_redir(t_shell *shell, t_redir *cmd);
void	run_heredoc(t_shell *shell, t_here *here);
void	run_block(t_shell *shell, t_block *cmd);

void	run_builtin(t_shell *shell, t_exec *cmd);
void	ms_echo(t_exec *cmd);
void	ms_pwd(t_shell *shell, t_exec *cmd);
void	ms_export(t_shell *shell, t_exec *cmd);
void	ms_cd(t_shell *shell, t_exec *cmd);
void	ms_unset(t_shell *shell, t_exec *cmd);
void	ms_env(t_shell *shell, t_exec *cmd);
void	ms_exit(t_shell *shell, t_exec *cmd);

#endif
