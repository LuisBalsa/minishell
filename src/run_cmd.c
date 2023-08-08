/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:32:04 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/08 17:40:21 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	run_cmd(t_shell *shell)
{
	if (shell->cmd->type == EXEC)
		exec_cmd(shell, shell->cmd);
	else if (shell->cmd->type == REDIR)
		redir_cmd(shell, shell->cmd);
	else if (shell->cmd->type == PIPE)
		pipe_cmd(shell, shell->cmd);
	else if (shell->cmd->type == BLOCK)
		block_cmd(shell, shell->cmd);
	else if (shell->cmd->type == AND)
		and_cmd(shell, shell->cmd);
	else if (shell->cmd->type == OR)
		or_cmd(shell, shell->cmd);
}
