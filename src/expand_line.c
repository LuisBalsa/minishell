/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:45:50 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/09 10:48:53 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand(char *key, int i, int j, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(shell->line, 0, i);
	tmp2 = ft_substr(shell->line, j, ft_strlen(shell->line) - j + 1);
//	free(shell->line);
	shell->line = ft_strjoin(tmp, key);
//	free(tmp);
	tmp = shell->line;
	shell->line = ft_strjoin(shell->line, tmp2);
//	free(tmp);
//	free(tmp2);
}

static void	tilde_to_expand(char *tmp, t_shell *shell)
{
	int	tilde;

	tilde = tmp - shell->line;
	if (!tmp[1] || ft_strchr(" /", tmp[1]))
		expand(get_env("HOME", shell), tilde, tilde + 1, shell);
	else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(" /", tmp[2])))
		expand(get_env("PWD", shell), tilde, tilde + 2, shell);
	else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(" /", tmp[2])))
		expand(get_env("OLDPWD", shell), tilde, tilde + 2, shell);
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
			tilde_to_expand(tmp, shell);
		tmp++;
	}
	if (dquote || squote)
		print_error(ERROR_QUOTE, RESTORE, shell);
}

void	expand_line(t_shell *shell)
{
	expand_tilde(shell);
//	expand_env(shell);
}
