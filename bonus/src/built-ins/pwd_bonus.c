/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:30:53 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/13 11:58:52 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	ms_pwd(t_shell *shell, t_exec *cmd)
{
	char	*path;

	if (cmd->argv[1] && cmd->argv[1][0] == '-')
	{
		print_error(shell, cmd->argv[0], "flags not supported", 2);
		return ;
	}
	path = getcwd(NULL, 0);
	if (!path)
		print_error(shell, cmd->argv[0], "couldn't get current directory", 2);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	if (shell->status == CONTINUE)
		g_exit = 0;
}
