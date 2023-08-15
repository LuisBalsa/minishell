/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:32:04 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 22:43:12 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

static void	run_pipe(t_shell *shell, t_pipe *cmd)
{
	int		fd[2];

	check(pipe(fd), shell, "pipe error", 127);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	run_cmd(shell, cmd->left);
	close(fd[1]);
	dup2(fd[0], STDOUT_FILENO);
	run_cmd(shell, cmd->right);
}

static void	run_and(t_shell *shell, t_lrn *cmd)
{
	run_cmd(shell, cmd->left);
	if (g_exit)
		run_cmd(shell, cmd->right);
	else
		run_cmd(shell, cmd->next);
}

static void	run_or(t_shell *shell, t_lrn *cmd)
{
	run_cmd(shell, cmd->left);
	if (!g_exit)
		run_cmd(shell, cmd->right);
	else
		run_cmd(shell, cmd->next);
}

void	run_cmd(t_shell *shell, t_cmd *cmd)
{
	if (shell->cmd->type == EXEC)
		run_exec(shell, (t_exec *)shell->cmd);
	else if (shell->cmd->type == REDIR)
		run_redir(shell, (t_redir *)shell->cmd);
	else if (shell->cmd->type == HERE_DOC)
		run_heredoc(shell, (t_here *)shell->cmd);
	else if (shell->cmd->type == PIPE)
		run_pipe(shell, (t_pipe *)shell->cmd);
	else if (shell->cmd->type == AND)
		run_and(shell, (t_lrn *)shell->cmd);
	else if (shell->cmd->type == OR_OP)
		run_or(shell, (t_lrn *)shell->cmd);
}
