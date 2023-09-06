/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:45:50 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/06 02:17:01 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	point_to_expand(int point, char *tmp, t_shell *sh)
{
	char	*key;
	int		len;

	if (*tmp == '~')
	{
		if (!tmp[1] || ft_strchr(NOT_EXP, tmp[1]))
			return (expand(get_env("HOME", sh), point, point + 1, &sh->line));
		else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
			return (expand(get_env("PWD", sh), point, point + 2, &sh->line));
		else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
			return (expand(get_env("OLDPWD", sh), point, point + 2, &sh->line));
	}
	else if (*tmp == '$' && tmp[1] == '?')
		return (expand_free(ft_itoa(g_exit), point, point + 2, &sh->line));
	else if (*tmp == '$' && tmp[1])
	{
		len = 1;
		while (ft_isalnum(tmp[len]) || tmp[len] == '_')
			len++;
		key = ft_substr(tmp, 1, len - 1);
		expand(get_env(key, sh), point, point + len, &sh->line);
		return (free(key), 1);
	}
	return (0);
}

static int	expand_tilde(t_shell *shell)
{
	int		dquote;
	int		squote;
	char	*tmp;

	dquote = 0;
	squote = 0;
	tmp = shell->line;
	while (*tmp)
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == '~' && !dquote && !squote
			&& (tmp == shell->line || ft_strchr(SPACES, *(tmp - 1))))
			if (point_to_expand(tmp - shell->line, tmp, shell))
				tmp = shell->line;
		if (*tmp)
			tmp++;
	}
	if (dquote || squote)
		return (print_error(shell, ERROR_QUOTE, NULL, 2));
	return (0);
}

static void	expand_env(t_shell *shell)
{
	int		dquote;
	int		squote;
	int		here;
	char	*tmp;

	dquote = 0;
	squote = 0;
	here = 0;
	tmp = shell->line - 1;
	while (*(++tmp))
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if ((*tmp == '<' && *(tmp + 1) == '<') && !dquote && !squote)
			here = 1;
		if (here && *tmp != '<' && *tmp != ' ')
			here = 2;
		if (*tmp == ' ' && here == 2 && !dquote && !squote)
			here = 0;
		if (*tmp == '$' && !ft_strchr(NOT_EXP, *(tmp + 1)) && !squote && !here)
			if (point_to_expand(tmp - shell->line, tmp, shell))
				tmp = shell->line - 1;
	}
}

static void	expand_space_operators(t_shell *sh, char *tmp)
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
}

int	expand_line(t_shell *shell)
{
	if (expand_tilde(shell))
		return (0);
	expand_env(shell);
	expand_wildcard(shell);
	expand_space_operators(shell, shell->line - 1);
	shell->line_len = ft_strlen(shell->line);
	return (1);
}
