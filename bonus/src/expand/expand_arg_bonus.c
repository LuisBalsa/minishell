/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:45:50 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/14 22:57:35 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static int	point_to_exp_tilde(t_shell *sh, int point, char *tmp, char **line)
{
	if (!tmp[1] || ft_strchr(NOT_EXP, tmp[1]))
		return (expand(env_get("HOME", sh), point, point + 1, line));
	else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
		return (expand(env_get("PWD", sh), point, point + 2, line));
	else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
		return (expand(env_get("OLDPWD", sh), point, point + 2, line));
	else if (*tmp == '$' && tmp[1] == '?')
		return (expand_free(ft_itoa(g_exit), point, point + 2, line));
	return (0);
}

static int	expand_tilde(t_shell *shell, char **line)
{
	int		dquote;
	int		squote;
	char	*tmp;

	dquote = 0;
	squote = 0;
	tmp = *line;
	while (*tmp)
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == '~' && !dquote && !squote
			&& (tmp == *line || ft_strchr(SPACES, *(tmp - 1))))
			if (point_to_exp_tilde(shell, tmp - *line, tmp, line))
				tmp = *line;
		if (*tmp)
			tmp++;
	}
	return (0);
}

static int	point_to_expand_env(t_shell *sh, int point, char *tmp, char **line)
{
	char	*key;
	int		len;

	if (tmp[1] == '?')
		return (expand_free(ft_itoa(g_exit), point, point + 2, line));
	else if (tmp[1])
	{
		len = 1;
		while (ft_isalpha(tmp[len]) || tmp[len] == '_')
			len++;
		len += (ft_isalnum(tmp[len]) > 0);
		while (len > 2 && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
			len++;
		key = ft_substr(tmp, 1, len - 1);
		expand(env_get(key, sh), point, point + len, line);
		return (free(key), 1);
	}
	return (0);
}

static void	env_expand(t_shell *shell, char *tmp, char **line)
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
		if (*tmp == '$' && !ft_strchr(NOT_EXP, *(tmp + 1)) && !squote
			&& !((dquote || squote) && (*(tmp + 1) == '"'
					|| *(tmp + 1) == '\'')))
		{
			if (point_to_expand_env(shell, tmp - *line, tmp, line))
			{
				tmp = *line - 1;
				dquote = 0;
				squote = 0;
			}
		}
	}
}

void	expand_arg(t_shell *shell, char **arg)
{
	expand_tilde(shell, arg);
	env_expand(shell, *arg - 1, arg);
	expand_wildcard(arg);
}
