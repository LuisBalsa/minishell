/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:32:58 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 01:09:25 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_lr	*lr_tmp;
	t_here	*here_tmp;
	t_redir	*redir_tmp;

	if (!cmd)
		return ;
	if (cmd->type == OR_OP || cmd->type == AND || cmd->type == PIPE)
	{
		lr_tmp = (t_lr *)cmd;
		free_cmd((t_cmd *)lr_tmp->left);
		free_cmd((t_cmd *)lr_tmp->right);
	}
	if (cmd->type == HERE_DOC)
	{
		here_tmp = (t_here *)cmd;
		free_cmd((t_cmd *)here_tmp->cmd);
	}
	if (cmd->type == REDIR)
	{
		redir_tmp = (t_redir *)cmd;
		free_cmd((t_cmd *)redir_tmp->cmd);
	}
	free(cmd);
	cmd = NULL;
}
