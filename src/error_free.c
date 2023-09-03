/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:15:18 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/03 15:14:17 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_exit(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	free_cmd(shell->cmd);
	envp_destroy(shell->env);
	if (shell->envp)
		ft_free_array(shell->envp);
	exit(g_exit);
}

int	check_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
		perror("fork");
		g_exit = 127;
	}
	return (pid);
}

void	check(int result, char *msg, int exit)
{
	if (result == -1)
	{
		ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
		perror(msg);
		g_exit = exit;
	}
}

int	print_error_syntax(t_shell *shell, char *msg, int exit)
{
	ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (*msg == '\0')
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (*msg && *(msg + 1) == *msg)
	{
		ft_putchar_fd(*msg, STDERR_FILENO);
		ft_putchar_fd(*msg, STDERR_FILENO);
	}
	else
		ft_putchar_fd(*msg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	shell->status = RESTORE;
	g_exit = exit;
	return (1);
}

int	print_error(t_shell *shell, char *msg, char *msg2, int exit)
{
	ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (msg2)
		ft_putstr_fd(": ", STDERR_FILENO);
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl_fd(msg2, STDERR_FILENO);
	shell->status = RESTORE;
	g_exit = exit;
	return (1);
}
