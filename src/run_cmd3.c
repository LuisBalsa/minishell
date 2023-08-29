/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:42:00 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/29 16:43:45 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_block(t_shell *shell, t_block *cmd)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	status = 0;
	if (pipe(pipefd) == -1)
		print_error(shell, "pipe error", NULL, 127);
	pid = fork();
	if (pid == -1)
		print_error(shell, "fork error", NULL, 127);
	if (pid == 0)
	{
		close(pipefd[0]);
		run_cmd(shell, cmd->block);
		exit(g_exit);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = WTERMSIG(status) + 128;
	}
}
