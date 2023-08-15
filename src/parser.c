/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:10:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 01:46:06 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	gettoken_type(t_shell *shell)
{
	int	type;

	type = *shell->ps;
	if (*shell->ps == '<')
	{
		if (*(shell->ps + 1) == '<')
			type = HERE_DOC;
	}
	else if (*shell->ps == '>')
	{
		if (*(shell->ps + 1) == '>')
			type = APPEND;
	}
	else if (*shell->ps == '|')
	{
		if (*(shell->ps + 1) == '|')
			type = OR_OP;
	}
	else if (*shell->ps && !ft_strchr(OPERATORS, *shell->ps))
		type = 'a';
	if (*shell->ps)
		shell->ps += (type == HERE_DOC || type == APPEND || type == OR_OP
				|| *shell->ps == '&') + 1;
	return (type);
}

int	gettoken(t_shell *sh, char **token)
{
	int		type;

	while (sh->ps < sh->es && !*sh->ps)
		sh->ps++;
	if (token)
		*token = sh->ps;
	type = gettoken_type(sh);
	ft_printf("type: %d\n", type);
	if (type == 'a')
		while (sh->ps < sh->es && *sh->ps && !ft_strchr(OPERATORS, *sh->ps))
			sh->ps++;
	while (sh->ps < sh->es && !*sh->ps)
		sh->ps++;
	return (type);
}

int	peek(t_shell *shell, char *op, int mode)
{
	while (shell->ps < shell->es && !*shell->ps)
		shell->ps++;
	if (mode == 2)
		return (shell->ps < shell->es && ft_strchr(op, *shell->ps)
			&& *(shell->ps + 1) == *shell->ps);
	return (shell->ps < shell->es && ft_strchr(op, *shell->ps)
		&& *(shell->ps + 1) != *shell->ps);
}

int	parser(t_shell *shell)
{
	shell->ps = shell->line;
	shell->es = shell->line + shell->line_len;
	shell->cmd = parseline(shell);
	ft_printf("cmd: %d\n", shell->cmd->type);
	ft_printf("status: %d\n", shell->status);
	ft_printf("ps: %s\n", shell->ps);
	peek(shell, "", 0);
	if (shell->ps != shell->es && shell->status != 2)
		return (!print_error_syntax(shell, shell->ps, 2));
	return (1);
}
