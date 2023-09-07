/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_constructors2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:33:34 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/07 23:37:00 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*block_cmd(t_cmd *cmd)
{
	t_block	*new;

	if (!cmd)
		return (NULL);
	new = (t_block *)ft_calloc(1, sizeof(t_block));
	new->type = BLOCK;
	new->cmd = cmd;
	return ((t_cmd *)new);
}
