/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:52:02 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/13 13:08:06 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static t_cmd	*parseredir(t_cmd *cmd, t_shell *shell)
{
	int		type;
	char	*token;

	while (peek(shell, "<>", 1) || peek(shell, "<>", 2))
	{
		type = gettoken(shell, NULL);
		if (gettoken(shell, &token) != 'a')
		{
			if (type != '<' || (type == '<' && ft_strcmp(token, ">")))
				return (print_error_syntax(shell, token, 2), cmd);
			else
				if (gettoken(shell, &token) != 'a')
					return (print_error_syntax(shell, token, 2), cmd);
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

	if (!peek(shell, "(", 1) && !peek(shell, "(", 2))
	{
		print_error(shell, "parsblock", NULL, 2);
		return (NULL);
	}
	gettoken(shell, NULL);
	cmd = block_cmd(parseline(shell));
	if (!cmd)
		return (NULL);
	if (!peek(shell, ")", 1) && !peek(shell, ")", 2)
		&& shell->status == CONTINUE)
	{
		print_error(shell, "open parenthesis not suported", NULL, 2);
		return (cmd);
	}
	gettoken(shell, NULL);
	return (parseredir(cmd, shell));
}

static t_cmd	*parseexec(t_shell *shell)
{
	t_cmd	*ret;
	t_exec	*cmd;
	char	*token;
	int		type;

	if (peek(shell, "(", 1) || peek(shell, "(", 2))
		return (parseblock(shell));
	ret = exec_cmd();
	cmd = (t_exec *)ret;
	ret = parseredir(ret, shell);
	while (!peek(shell, "|&)", 1) && !peek(shell, "|&)", 2))
	{
		type = gettoken(shell, &token);
		if (!type)
			break ;
		if (type != 'a' && shell->status == CONTINUE)
			return (print_error_syntax(shell, token, 2), ret);
		if (cmd->argv[0])
			cmd->argv[0] = ft_strjoin_free_s1(cmd->argv[0], " ");
		cmd->argv[0] = ft_strjoin_free_s1(cmd->argv[0], token);
		ret = parseredir(ret, shell);
	}
	return (ret);
}

static t_cmd	*parsepipeline(t_shell *shell)
{
	t_cmd	*cmd;

	if (peek(shell, "|&", 1) && shell->status == CONTINUE)
		return (print_error_syntax(shell, shell->ps, 2), NULL);
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
		if (peek(shell, "|&", 2))
			return (print_error_syntax(shell, shell->ps, 2), cmd);
		if (type == OR_OP)
			cmd = or_cmd(cmd, parseline(shell));
		else if (type == '&')
			cmd = and_cmd(cmd, parseline(shell));
	}
	return (cmd);
}
