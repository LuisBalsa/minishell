/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:22 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/11 14:22:17 by luide-so         ###   ########.fr       */
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
	if (shell->line[0] == '|')
		return (print_error("syntax error near unexpected token `|'", 2));
	if (shell->line[0] == ';')
		return (print_error("syntax error near unexpected token `;'", 2));
	if (shell->line[0] == '<')
		return (print_error("syntax error near unexpected token `<'", 2));
	if (shell->line[0] == '>')
		return (print_error("syntax error near unexpected token `>'", 2));
	if (shell->line[0] == '&')
		return (print_error("syntax error near unexpected token `&'", 2));
	return (0);
}

void	pipe_continuation(t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	if (shell->line[ft_strlen(shell->line) - 1] == '|')
	{
		tmp = readline("> ");
		tmp2 = ft_strjoin(shell->line, tmp);
		free(shell->line);
		trim_spaces(&tmp2);
		shell->line = tmp2;
		free(tmp);
		pipe_continuation(shell);
	}
}

int	init_line(t_shell *shell)
{
	shell->status = CONTINUE;
	if (only_spaces(shell->line))
		return (0);
	trim_spaces(&shell->line);
	if (syntax_error(shell))
		return (add_history(shell->line), 0);
	pipe_continuation(shell);
	add_history(shell->line);
	shell->es = shell->line + ft_strlen(shell->line);
	return (1);
}
