/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:52:02 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/13 12:52:19 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parseline(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = NULL;
	while (shell->ps < shell->es)
	{
		if (peek(shell, "|;"))
			shell->ps++;
		if (peek(shell, "|;"))
			return (print_error(ERROR_SINTAX, 2) ? NULL : NULL);
		tmp = gettoken(shell);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&cmd, ft_lstnew(tmp));
	}
	return (cmd);
}
