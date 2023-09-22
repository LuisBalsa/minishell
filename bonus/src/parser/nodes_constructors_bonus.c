/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_constructors_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:53:28 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/13 11:59:45 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd)
{
	t_redir	*redir;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	redir->type = REDIR;
	redir->file = ft_strdup(file);
	redir->mode = mode;
	redir->fd = fd;
	if (cmd->type == EXEC || cmd->type == BLOCK)
		redir->cmd = cmd;
	else
	{
		tmp = cmd;
		while (tmp->type != EXEC && tmp->type != BLOCK)
		{
			tmp2 = tmp;
			tmp = ((t_redir *)tmp)->cmd;
		}
		((t_redir *)tmp2)->cmd = (t_cmd *)redir;
		redir->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)redir);
}

t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*exec_cmd(void)
{
	t_exec	*cmd;

	cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*and_cmd(t_cmd *left, t_cmd *right)
{
	t_lrn	*cmd;

	cmd = (t_lrn *)ft_calloc(1, sizeof(t_lrn));
	cmd->type = AND;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*or_cmd(t_cmd *left, t_cmd *right)
{
	t_lrn	*cmd;

	cmd = (t_lrn *)ft_calloc(1, sizeof(t_lrn));
	cmd->type = OR_OP;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
