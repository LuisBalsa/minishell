/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:22 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/07 13:14:18 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	trim_spaces(char **line)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strtrim(*line, SPACES);
	free(tmp);
}

static int	syntax_error(t_shell *shell)
{
	int		dquote;
	int		squote;
	char	*tmp;

	dquote = 0;
	squote = 0;
	tmp = shell->line - 1;
	if (ft_strchr("|;&", *shell->line))
		return (print_error_syntax(shell, shell->line, 2));
	if (shell->line[ft_strlen(shell->line) - 1] == '|'
		|| ft_strcmp(shell->line + ft_strlen(shell->line) - 2, "||") == 0
		|| ft_strcmp(shell->line + ft_strlen(shell->line) - 2, "&&") == 0)
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
	return (0);
}

int	init_line(t_shell *shell)
{
	shell->status = CONTINUE;
	if (only_spaces(shell->line))
		return (0);
	add_history(shell->line);
	trim_spaces(&shell->line);
	if (syntax_error(shell))
		return (0);
	return (1);
}