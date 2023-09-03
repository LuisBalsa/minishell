/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:42:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/03 15:41:44 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_heredoc(t_shell *shell, char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			tmp = ft_itoa(g_exit);
			expand(tmp, i, i + 2, line);
			free(tmp);
		}
		else if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
		{
			j = i + 1;
			while (ft_isalnum((*line)[j]) || (*line)[j] == '_')
				j++;
			tmp = ft_substr(*line, i + 1, j - i - 1);
			expand(get_env(tmp, shell), i, j, line);
			free(tmp);
		}
		i++;
	}
}

static void	heredoc_reader(t_shell *shell, t_here *here, int fd)
{
	char	*line;

	fd = open("here_doc", here->mode, 0644);
	dup2(here->fdin, STDIN_FILENO);
	dup2(here->fdout, STDOUT_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(ERROR_TITLE ERROR_HERE_DOC "%s'\n", here->eof);
			break ;
		}
		if (ft_strcmp(line, here->eof) == 0)
		{
			free(line);
			break ;
		}
		expand_heredoc(shell, &line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	g_exit = 0;
	free_exit(shell);
}

void	run_heredoc(t_shell *shell, t_here *here)
{
	int		fd;
	pid_t	pid;

	sig_handler(SIGIGNORE);
	pid = check_fork();
	if (pid == 0)
	{
		sig_handler(SIGHEREDOC);
		heredoc_reader(shell, here, 0);
	}
	waitpid(pid, &g_exit, 0);
	g_exit = WEXITSTATUS(g_exit);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (g_exit == 0)
		run_cmd(shell, here->cmd);
	dup2(here->fdin, STDIN_FILENO);
	unlink("here_doc");
}

t_cmd	*here_cmd(t_cmd *cmd, char *eof)
{
	t_here	*here;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HERE_DOC;
	here->eof = eof;
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	here->fdin = dup(STDIN_FILENO);
	here->fdout = dup(STDOUT_FILENO);
	if (cmd->type == EXEC || cmd->type == REDIR)
		here->cmd = cmd;
	else
	{
		tmp = cmd;
		while (tmp->type != EXEC && tmp->type != REDIR)
		{
			tmp2 = tmp;
			tmp = ((t_redir *)tmp)->cmd;
		}
		((t_redir *)tmp2)->cmd = (t_cmd *)here;
		here->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)here);
}
