/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_constructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:53:28 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 01:14:26 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd)
{
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	redir->cmd = cmd;
	redir->type = REDIR;
	redir->file = file;
	redir->mode = mode;
	redir->fd = fd;
	return ((t_cmd *)redir);
}

t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_lr	*cmd;

	cmd = (t_lr *)ft_calloc(1, sizeof(t_lr));
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
	t_lr	*cmd;

	cmd = (t_lr *)ft_calloc(1, sizeof(t_lr));
	cmd->type = AND;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*or_cmd(t_cmd *left, t_cmd *right)
{
	t_lr	*cmd;

	cmd = (t_lr *)ft_calloc(1, sizeof(t_lr));
	cmd->type = OR_OP;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
