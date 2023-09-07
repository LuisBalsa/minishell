/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:10:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/07 13:13:37 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	trim_quotes_and_advance(char **ps, t_shell *shell)
{
	char	*tmp;
	int		squote;
	int		dquote;

	dquote = 0;
	squote = 0;
	tmp = *ps;
	while (*tmp && (!ft_strchr(OPERATORS, *tmp) || squote || dquote))
	{
		if ((*tmp == '"' || *tmp == '\'') && !squote && !dquote)
		{
			dquote = (*tmp == '"');
			squote = (*tmp == '\'');
			memmove(tmp, tmp + 1, shell->line_len - (tmp - shell->line));
		}
		else if ((*tmp == '"' && dquote) || (*tmp == '\'' && squote))
		{
			dquote -= (*tmp == '"');
			squote -= (*tmp == '\'');
			memmove(tmp, tmp + 1, shell->line_len - (tmp - shell->line));
		}
		else
			tmp++;
	}
	*ps = tmp;
}

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
	if (*shell->ps && type != 'a')
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
	if (type == 'a')
		trim_quotes_and_advance(&sh->ps, sh);
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
	peek(shell, "", 0);
	if (shell->ps != shell->es && shell->status != 2)
		return (!print_error_syntax(shell, shell->ps, 2));
	return (1);
}
