/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:10:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/10 21:30:33 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser(t_shell *shell)
{
	shell->cmd = NULL;
	shell->es = shell->line + ft_strlen(shell->line);
	parseline(shell);
	peek(shell, "");
	if (shell->es != shell->line)
		return (!print_error(ERROR_SINTAX, 2));
	return (0);
}
