/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:42:13 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/19 12:37:29 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_heredoc(t_shell *shell, char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			tmp = ft_itoa(g_exit);
			expand(tmp, i, i + 2, line);
			free(tmp);
		}
		else if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
		{
			j = i + 1;
			while (ft_isalnum((*line)[j]) || (*line)[j] == '_')
				j++;
			tmp = ft_substr(*line, i + 1, j - i - 1);
			expand(get_env(tmp, shell), i, j, line);
			free(tmp);
		}
		i++;
	}
}

static void	heredoc(t_shell *shell, t_here *here)
{
	char	*line;
	int		fd;

	fd = open("here_doc", here->mode, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(ERROR_TITLE ERROR_HERE_DOC "%s'\n", here->eof);
			break ;
		}
		if (ft_strcmp(line, here->eof) == 0)
		{
			free(line);
			break ;
		}
		expand_heredoc(shell, &line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	run_heredoc(t_shell *shell, t_here *here)
{
	int	fd;
	int	original_fd;

	original_fd = dup(STDIN_FILENO);
	heredoc(shell, here);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	run_cmd(shell, here->cmd);
	dup2(original_fd, STDIN_FILENO);
	unlink("here_doc");
}

t_cmd	*here_cmd(t_cmd *cmd, char *eof)
{
	t_here	*here;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->cmd = cmd;
	here->type = HERE_DOC;
	here->eof = eof;
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	here->fd = 0;
	return ((t_cmd *)here);
}
