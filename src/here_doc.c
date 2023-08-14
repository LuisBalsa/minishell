/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:42:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/14 18:39:48 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*here_cmd(char *eof)
{
	t_here	*cmd;

	cmd = (t_here *)ft_calloc(1, sizeof(t_here));
	cmd->type = HERE_DOC;
	cmd->eof = eof;
	cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd = 0;
	return ((t_cmd *)cmd);
}
