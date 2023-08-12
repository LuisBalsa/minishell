/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:48:06 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/12 02:13:59 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	trim_quotes(char *s, int squote, int dquote, t_shell *shell)
{
	int		i;

	i = -1;
	while (++i < shell->line_len)
	{
		if ((s[i] == '"' || s[i] == '\'') && !squote && !dquote)
		{
			dquote = (s[i] == '"');
			squote = (s[i] == '\'');
			if (!i || !s[i - 1])
				s[i] = '\0';
			else
				memmove(&s[i], &s[i + 1], shell->line_len - i);
		}
		else if ((s[i] == '"' && dquote) || (s[i] == '\'' && squote))
		{
			dquote -= (s[i] == '"');
			squote -= (s[i] == '\'');
			if (!s[i + 1])
				s[i] = '\0';
			else
				memmove(&s[i], &s[i + 1], shell->line_len - i);
		}
	}
}

static void	trim_spaces(char *line)
{
	char	*tmp;
	int		squote;
	int		dquote;

	dquote = 0;
	squote = 0;
	tmp = line;
	while (*tmp)
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == ' ' && !dquote && !squote)
			*tmp = '\0';
		tmp++;
	}
}

void	trim_line(t_shell *shell)
{
	trim_spaces(shell->line);
	trim_quotes(shell->line, 0, 0, shell);
}
