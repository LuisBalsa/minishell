/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:32:04 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/30 18:12:32 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

static void	fork_exec_pipe(t_shell *shell, t_cmd *cmd, int *fd, int std)
{
	if (cmd->type == EXEC)
	{
		shell->pid = fork();
		check(shell->pid, "fork error", 127);
		if (shell->pid == 0)
		{
			check(dup2(fd[std], std), "dup2 error", 127);
			check(close(fd[std]), "close error", 127);
			run_cmd(shell, cmd);
			exit(g_exit);
		}
		check(close(fd[std]), "close error", 127);
	}
	else
	{
		check(close(fd[std]), "close error", 127);
		run_cmd(shell, cmd);
	}
}

static void	run_pipe(t_shell *shell, t_pipe *cmd)
{
	int		fd[2];

	sig_handler(SIGCHILD);
	check(pipe(fd), "pipe error", 127);
	fork_exec_pipe(shell, cmd->left, fd, STDOUT_FILENO);
	fork_exec_pipe(shell, cmd->right, fd, STDIN_FILENO);
}

static void	run_and(t_shell *shell, t_lrn *cmd)
{
	run_cmd(shell, cmd->left);
	wait_children(shell);
	if (!g_exit)
		run_cmd(shell, cmd->right);
	wait_children(shell);
	run_cmd(shell, cmd->next);
}

static void	run_or(t_shell *shell, t_lrn *cmd)
{
	run_cmd(shell, cmd->left);
	wait_children(shell);
	if (g_exit)
		run_cmd(shell, cmd->right);
	wait_children(shell);
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
	else if (cmd->type == BLOCK)
		run_block(shell, (t_block *)cmd);
}
