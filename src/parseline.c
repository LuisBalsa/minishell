/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:52:02 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/15 01:52:09 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_cmd	*parseredir(t_cmd *cmd, t_shell *shell)
{
	int		type;
	char	*token;

	while (peek(shell, "<>", 1))
	{
		ft_printf("redir sao dois tokens:\n");
		type = gettoken(shell, NULL);
		if (gettoken(shell, &token) != 'a')
		{
			print_error_syntax(shell, token, 2);
			return (cmd);
		}
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
	ft_printf("parsblock primeiro token:\n");
	gettoken(shell, NULL);
	cmd = parseline(shell);
	if (!peek(shell, ")", 1))
	{
		print_error(shell, "open parenthesis not suported", 2);
		return (cmd);
	}
	if (!cmd)
		return (NULL);
	ft_printf("parsblock segundo token:\n");
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
		ft_printf("parseexec token:\n");
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
		ft_printf("parsepipeline token:\n");
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
		ft_printf("parseline token:\n");
		type = gettoken(shell, NULL);
		if (type == OR_OP)
			cmd = or_cmd(cmd, parseline(shell));
		else if (type == '&')
			cmd = and_cmd(cmd, parseline(shell));
	}
	return (cmd);
}
