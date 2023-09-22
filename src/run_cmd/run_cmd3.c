/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:42:00 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/12 00:41:55 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_block(t_shell *shell, t_block *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error(shell, "fork error", NULL, 127);
	if (pid == 0)
	{
		run_cmd(shell, cmd->cmd);
		wait_children(shell);
		exit(g_exit);
	}
	waitpid(pid, &g_exit, 0);
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	else if (WIFSIGNALED(g_exit))
		g_exit = WTERMSIG(g_exit) + 128;
}

static int	expand_file_mane(t_shell *shell, char **file)
{
	int	len;

	if (ft_strchr(*file, '$') && ft_strchr(*file, '*'))
	{
		print_error(shell, *file, "ambiguous redirect", 1);
		return (0);
	}
	expand_arg(shell, file);
	len = ft_strlen(*file);
	trim_arg(*file);
	trim_quotes(*file, &len);
	return (1);
}

void	run_redir(t_shell *shell, t_redir *cmd)
{
	int		fd;
	int		original_fd;

	original_fd = dup(cmd->fd);
	fd = -2;
	if (expand_file_mane(shell, &cmd->file))
		fd = open(cmd->file, cmd->mode, 0644);
	if (fd == -1)
		print_error(shell, cmd->file, strerror(errno), 1);
	else if (shell->status == CONTINUE)
	{
		dup2(fd, cmd->fd);
		close(fd);
		run_cmd(shell, cmd->cmd);
	}
	check(dup2(original_fd, cmd->fd), "dup2 error", 1);
}
