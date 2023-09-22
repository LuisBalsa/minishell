/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:22 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/13 11:59:42 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static void	expand_line(t_shell *sh, char *tmp)
{
	int		dquote;
	int		squote;

	dquote = 0;
	squote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (ft_strchr(OPERATORS, *tmp) && !dquote && !squote)
		{
			if (tmp != sh->line && !ft_strchr(" |><&()", *(tmp - 1)))
			{
				if (expand(" ", tmp - sh->line, tmp - sh->line, &sh->line))
					tmp = sh->line - 1;
			}
			else if (!ft_strchr(" |><&()", *(tmp + 1)))
				if (expand(" ", tmp - sh->line + 1,
						tmp - sh->line + 1, &sh->line))
					tmp = sh->line - 1;
		}
	}
	sh->line_len = ft_strlen(sh->line);
}

static void	trim_line(t_shell *shell)
{
	char	*tmp;
	int		squote;
	int		dquote;

	dquote = 0;
	squote = 0;
	tmp = shell->line;
	while (*tmp)
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (ft_strchr(SPACES, *tmp) && !squote && !dquote)
			*tmp = '\0';
		tmp++;
	}
}

static int	syntax_error(t_shell *shell, int dquote, int squote)
{
	char	*tmp;

	tmp = shell->line - 1;
	if (ft_strchr("|;&", *shell->line))
		return (print_error_syntax(shell, shell->line, 2));
	if (shell->line[ft_strlen(shell->line) - 1] == '|'
		|| shell->line[ft_strlen(shell->line) - 1] == '&')
		return (print_error(shell,
				"Open | or || or && not supported", NULL, 2));
	while (*++tmp)
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == '&' && !dquote && !squote)
			if (*(tmp + 1) != '&' && *(tmp - 1) != '&')
				return (print_error(shell, "no support for single &", NULL, 2));
	}
	if (dquote || squote)
		return (print_error(shell, ERROR_QUOTE, NULL, 2));
	return (0);
}

int	init_line(t_shell *shell)
{
	char	*tmp;

	shell->status = CONTINUE;
	tmp = shell->line;
	shell->line = ft_strtrim(shell->line, SPACES);
	free(tmp);
	if (shell->line[0] == '\0')
		return (0);
	add_history(shell->line);
	if (syntax_error(shell, 0, 0))
		return (0);
	expand_line(shell, shell->line - 1);
	trim_line(shell);
	return (1);
}
