/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:50:09 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/13 11:59:14 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->argv[0])
		free(exec->argv[0]);
	free(exec);
	exec = NULL;
}

void	free_block(t_block *block)
{
	if (!block)
		return ;
	free_cmd(block->cmd);
	free(block);
	block = NULL;
}
