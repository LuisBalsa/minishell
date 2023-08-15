/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:42:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 01:13:29 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*here_cmd(t_cmd *cmd, char *eof)
{
	t_here	*here;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->cmd = cmd;
	here->type = HERE_DOC;
	here->eof = eof;
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	here->fd = 0;
	return ((t_cmd *)here);
}
