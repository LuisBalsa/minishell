/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:32:04 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/12 12:52:06 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_fds_and_sig_handler(int fd[2], int sig)
{
	if (sig)
		sig_handler(sig);
	check(close(fd[0]), "close error", 127);
	check(close(fd[1]), "close error", 127);
}

static void	run_pipe(t_shell *shell, t_pipe *cmd)
{
	int		fd[2];

	check(pipe(fd), "pipe error", 127);
	shell->pid = check_fork();
	if (shell->pid == 0)
	{
		check(dup2(fd[1], STDOUT_FILENO), "dup2 error", 127);
		close_fds_and_sig_handler(fd, SIGIGNORE);
		run_cmd(shell, cmd->left);
		free_exit(shell);
	}
	if (cmd->left->type == HERE_DOC)
		wait_children(shell);
	if (shell->status == CONTINUE)
		shell->pid = check_fork();
	if (shell->pid == 0)
	{
		check(dup2(fd[0], STDIN_FILENO), "dup2 error", 127);
		close_fds_and_sig_handler(fd, SIGIGNORE);
		run_cmd(shell, cmd->right);
		free_exit(shell);
	}
	close_fds_and_sig_handler(fd, 0);
	wait_children(shell);
}

static void	run_and(t_shell *shell, t_lrn *cmd)
{
	sig_handler(SIGCHILD);
	run_cmd(shell, cmd->left);
	shell->exec_cmd = !g_exit;
	run_cmd(shell, cmd->right);
}

static void	run_or(t_shell *shell, t_lrn *cmd)
{
	sig_handler(SIGCHILD);
	run_cmd(shell, cmd->left);
	shell->exec_cmd = (g_exit && g_exit != 130);
	run_cmd(shell, cmd->right);
}

void	run_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type == EXEC && shell->exec_cmd == true)
		run_exec(shell, (t_exec *)cmd);
	else if (cmd->type == REDIR && shell->exec_cmd == true)
		run_redir(shell, (t_redir *)cmd);
	else if (cmd->type == HERE_DOC)
		run_heredoc(shell, (t_here *)cmd);
	else if (cmd->type == PIPE)
		run_pipe(shell, (t_pipe *)cmd);
	else if (cmd->type == AND)
		run_and(shell, (t_lrn *)cmd);
	else if (cmd->type == OR_OP)
		run_or(shell, (t_lrn *)cmd);
	else if (cmd->type == BLOCK && shell->exec_cmd == true)
		run_block(shell, (t_block *)cmd);
}
