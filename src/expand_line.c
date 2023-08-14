/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:45:50 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/13 13:21:10 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	point_to_expand(int point, char *tmp, t_shell *shell)
{
	char	*key;
	int		len;

	if (*tmp == '~')
	{
		if (!tmp[1] || ft_strchr(" /", tmp[1]))
			return (expand(get_env("HOME", shell), point, point + 1, shell));
		else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(" /", tmp[2])))
			return (expand(get_env("PWD", shell), point, point + 2, shell));
		else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(" /", tmp[2])))
			return (expand(get_env("OLDPWD", shell), point, point + 2, shell));
	}
	else if (*tmp == '$' && tmp[1] == '?')
		return (expand_free(ft_itoa(g_exit), point, point + 2, shell));
	else if (*tmp == '$' && (ft_isalpha(tmp[1]) || tmp[1] == '_'))
	{
		len = 1;
		while (ft_isalnum(tmp[len]) || tmp[len] == '_')
			len++;
		key = ft_substr(tmp, 1, len - 1);
		expand(get_env(key, shell), point, point + len, shell);
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
		return (print_error(ERROR_QUOTE, 2));
	return (0);
}

static void	expand_env(t_shell *shell)
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
		if (*tmp == '$' && !ft_strchr(SPACES, *(tmp + 1)) && !squote)
			if (point_to_expand(tmp - shell->line, tmp, shell))
				tmp = shell->line;
		if (*tmp)
			tmp++;
	}
}

static void	expand_space_operators(t_shell *sh)
{
	int		dquote;
	int		squote;
	char	*tmp;

	dquote = 0;
	squote = 0;
	tmp = sh->line - 1;
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
				if (expand(" ", tmp - sh->line, tmp - sh->line, sh))
					tmp = sh->line - 1;
			}
			else if (!ft_strchr(" |><&()", *(tmp + 1)))
				if (expand(" ", tmp - sh->line + 1, tmp - sh->line + 1, sh))
					tmp = sh->line - 1;
		}
	}
}

int	expand_line(t_shell *shell)
{
	if (expand_tilde(shell))
		return (0);
	expand_env(shell);
	expand_space_operators(shell);
	shell->line_len = ft_strlen(shell->line);
	return (1);
}
