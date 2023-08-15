/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:32:58 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 13:30:27 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free_cmd(redir->cmd);
	free(redir);
	redir = NULL;
}

static void	free_here(t_here *here)
{
	if (!here)
		return ;
	free_cmd(here->cmd);
	free(here);
	here = NULL;
}

static void	free_pipe(t_pipe *pipe)
{
	if (!pipe)
		return ;
	free_cmd(pipe->left);
	free_cmd(pipe->right);
	free(pipe);
	pipe = NULL;
}

static void	free_lrn(t_lrn *lrn)
{
	if (!lrn)
		return ;
	free_cmd(lrn->left);
	free_cmd(lrn->right);
	free_cmd(lrn->next);
	free(lrn);
	lrn = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == OR_OP || cmd->type == AND)
		free_lrn((t_lrn *)cmd);
	else if (cmd->type == PIPE)
		free_pipe((t_pipe *)cmd);
	else if (cmd->type == HERE_DOC)
		free_here((t_here *)cmd);
	else if (cmd->type == REDIR)
		free_redir((t_redir *)cmd);
	else
		free (cmd);
}
