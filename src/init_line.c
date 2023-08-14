/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:22 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/13 17:57:35 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	trim_spaces(char **line)
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
	if (shell->line[0] == '|')
		return (print_error("syntax error near unexpected token `|'", 2));
	if (shell->line[0] == ';')
		return (print_error("syntax error near unexpected token `;'", 2));
	if (shell->line[0] == '&')
		return (print_error("syntax error near unexpected token `&'", 2));
	while (*++tmp)
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == '&' && !dquote && !squote)
			if (*(tmp + 1) != '&' && *(tmp - 1) != '&')
				return (print_error("no support for single &", 2));
	}
	return (0);
}

static int	pipe_continuation(t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	if (shell->line[ft_strlen(shell->line) - 1] == '|'
		|| ft_strcmp(shell->line + ft_strlen(shell->line) - 2, "||") == 0
		|| ft_strcmp(shell->line + ft_strlen(shell->line) - 2, "&&") == 0)
	{
		tmp = readline("> ");
		if (!tmp)
			return (shell->status = STOP, g_exit = 2, 1);
		tmp2 = ft_strjoin(shell->line, tmp);
		free(shell->line);
		trim_spaces(&tmp2);
		shell->line = tmp2;
		free(tmp);
		pipe_continuation(shell);
	}
	return (0);
}

int	init_line(t_shell *shell)
{
	shell->status = CONTINUE;
	if (only_spaces(shell->line))
		return (0);
	trim_spaces(&shell->line);
	if (syntax_error(shell))
		return (add_history(shell->line), 0);
	if (pipe_continuation(shell))
		return (add_history(shell->line), 0);
	add_history(shell->line);
	return (1);
}
