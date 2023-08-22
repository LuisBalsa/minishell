/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:43:31 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/22 22:49:40 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_builtin(t_shell *shell, t_exec *cmd)
{
	(void)shell;

	g_exit = 0;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		ms_echo(*cmd);
/* 	else if (!ft_strcmp(cmd->argv[0], "cd"))
		ms_cd(shell, cmd); */
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ms_pwd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ms_export(shell, cmd);
/* 	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ms_unset(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ms_env(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ms_exit(shell, cmd); */
}
