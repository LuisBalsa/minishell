/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:52:02 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/14 19:05:22 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parseredir(t_cmd *cmd, t_shell *shell)
{
	int		type;
	char	*token;

	while (peek(shell, "<>", 2))
	{
		type = gettoken(shell, NULL);
		if (gettoken(shell, &token) != 'a')
		{
			print_error_syntax(shell, token, 2);
			return (NULL);
		}
		if (type == '<')
			cmd = redir_cmd(token, O_RDONLY, 0);
		else if (type == '>')
			cmd = redir_cmd(token, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (type == APPEND)
			cmd = redir_cmd(token, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (type == HERE_DOC)
			cmd = here_cmd(token);
	}
	return (cmd);
}

t_cmd	*parseblock(t_shell *shell)
{
	t_cmd	*cmd;

	if (!peek(shell, "(", 1))
	{
		print_error(shell, "parsblock", 2);
		return (NULL);
	}
	gettoken(shell, NULL);
	cmd = parseline(shell);
	if (!peek(shell, ")", 1))
	{
		print_error(shell, "open parenthesis not suporrted", 2);
		return (NULL);
	}
	if (!cmd)
		return (NULL);
	gettoken(shell, NULL);
	return (parseredir(cmd, shell));
}

t_cmd	*parsepipeline(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = parseexec(shell);
	if (cmd && peek(shell, "|", 1))
	{
		gettoken(shell, NULL);
		cmd = pipe_cmd(cmd, parsepipeline(shell));
	}
	return (cmd);
}

t_cmd	*parseline(t_shell *shell)
{
	t_cmd	*cmd;
	int		type;

	cmd = parsepipeline(shell);
	if (cmd && peek(shell, "&|", 2))
	{
		type = gettoken(shell, NULL);
		if (type == OR_OP)
			cmd = or_cmd(cmd, parseline(shell));
		else if (type == '&')
			cmd = and_cmd(cmd, parseline(shell));
	}
	return (cmd);
}
