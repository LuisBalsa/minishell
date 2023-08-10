/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:45:50 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/10 13:03:01 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expand(char *key, int i, int j, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(shell->line, 0, i);
	tmp2 = ft_substr(shell->line, j, ft_strlen(shell->line) - j + 1);
	tmp3 = shell->line;
	free(tmp3);
	shell->line = ft_strjoin(tmp, key);
	free(tmp);
	tmp = shell->line;
	shell->line = ft_strjoin(shell->line, tmp2);
	free(tmp);
	free(tmp2);
	return (1);
}

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
		return (expand(ft_itoa(shell->status), point, point + 2, shell));
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

static void	expand_tilde(t_shell *shell)
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
			&& (tmp == shell->line || *(tmp - 1) == ' '))
			if (point_to_expand(tmp - shell->line, tmp, shell))
				tmp = shell->line;
		tmp++;
	}
	if (dquote || squote)
		print_error(ERROR_QUOTE, RESTORE, EXIT_FAILURE, shell);
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
		tmp++;
	}
}

void	expand_line(t_shell *shell)
{
	expand_tilde(shell);
	expand_env(shell);
}
