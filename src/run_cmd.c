/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:32:04 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/21 04:50:02 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

static void	fork_exec_pipe(t_shell *shell, t_cmd *cmd, int *fd, int std)
{
	int		pid;

	pid = fork();
	check(pid, "fork error", 127);
	if (pid == 0)
	{
		g_exit = 127;
		check(dup2(fd[std], std), "dup2 error", 127);
		run_cmd(shell, cmd);
		exit(g_exit);
	}
	else
	{
		check(close(fd[std]), "close error", 127);
		waitpid(pid, &g_exit, WUNTRACED);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		else if (WIFSIGNALED(g_exit))
			g_exit = WTERMSIG(g_exit) + 128;
	}
}

static void	run_pipe(t_shell *shell, t_pipe *cmd)
{
	int		fd[2];

	check(pipe(fd), "pipe error", 127);
	sig_handler(SIGIGNORE);
	fork_exec_pipe(shell, cmd->left, fd, STDOUT_FILENO);
	if (g_exit != 130 && g_exit != 131)
		fork_exec_pipe(shell, cmd->right, fd, STDIN_FILENO);
	sig_handler(SIGRESTORE);
}

static void	run_and(t_shell *shell, t_lrn *cmd)
{
	run_cmd(shell, cmd->left);
	if (!g_exit)
		run_cmd(shell, cmd->right);
	run_cmd(shell, cmd->next);
}

static void	run_or(t_shell *shell, t_lrn *cmd)
{
	run_cmd(shell, cmd->left);
	if (g_exit)
		run_cmd(shell, cmd->right);
	run_cmd(shell, cmd->next);
}

void	run_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type == EXEC)
		run_exec(shell, (t_exec *)cmd);
	else if (cmd->type == REDIR)
		run_redir(shell, (t_redir *)cmd);
	else if (cmd->type == HERE_DOC)
		run_heredoc(shell, (t_here *)cmd);
	else if (cmd->type == PIPE)
		run_pipe(shell, (t_pipe *)cmd);
	else if (cmd->type == AND)
		run_and(shell, (t_lrn *)cmd);
	else if (cmd->type == OR_OP)
		run_or(shell, (t_lrn *)cmd);
}
