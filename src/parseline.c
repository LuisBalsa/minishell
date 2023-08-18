/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:52:02 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/18 02:43:57 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_cmd	*parseredir(t_cmd *cmd, t_shell *shell)
{
	int		type;
	char	*token;

	if (peek(shell, "<>", 1) || peek(shell, "<>", 2))
	{
		type = gettoken(shell, NULL);
		if (gettoken(shell, &token) != 'a')
		{
			print_error_syntax(shell, token, 2);
			return (cmd);
		}
		cmd = parseredir(cmd, shell);
		if (type == '<')
			cmd = redir_cmd(cmd, token, O_RDONLY, 0);
		else if (type == '>')
			cmd = redir_cmd(cmd, token, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (type == APPEND)
			cmd = redir_cmd(cmd, token, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (type == HERE_DOC)
			cmd = here_cmd(cmd, token);
	}
	return (cmd);
}

static t_cmd	*parseblock(t_shell *shell)
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
		print_error(shell, "open parenthesis not suported", 2);
		return (cmd);
	}
	if (!cmd)
		return (NULL);
	gettoken(shell, NULL);
	return (parseredir(cmd, shell));
}

static t_cmd	*parseexec(t_shell *shell)
{
	t_cmd	*ret;
	t_exec	*cmd;
	char	*token;
	int		type;
	int		argc;

	if (peek(shell, "(", 1))
		return (parseblock(shell));
	ret = exec_cmd();
	cmd = (t_exec *)ret;
	argc = 0;
	ret = parseredir(ret, shell);
	while (!peek(shell, "|&)", 1) && !peek(shell, "|&", 2))
	{
		type = gettoken(shell, &token);
		if (!type)
			break ;
		if (type != 'a')
			return (print_error_syntax(shell, token, 2), ret);
		cmd->argv[argc++] = token;
		if (argc >= MAXARGS)
			return (print_error(shell, "too many arguments", 2), ret);
		ret = parseredir(ret, shell);
	}
	return (ret);
}

static t_cmd	*parsepipeline(t_shell *shell)
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
			cmd = or_cmd(cmd, parsepipeline(shell), parseline(shell));
		else if (type == '&')
			cmd = and_cmd(cmd, parsepipeline(shell), parseline(shell));
	}
	return (cmd);
}
