/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:42:00 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/30 15:16:13 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_block(t_shell *shell, t_block *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error(shell, "fork error", NULL, 127);
	if (pid == 0)
	{
		run_cmd(shell, cmd->block);
		wait_children(shell);
		exit(g_exit);
	}
	waitpid(pid, &g_exit, 0);
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	else if (WIFSIGNALED(g_exit))
		g_exit = WTERMSIG(g_exit) + 128;
}
