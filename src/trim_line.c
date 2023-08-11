/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:48:06 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/11 11:05:32 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	add_null(char *tmp, int i, int j, t_shell *shell)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_substr(shell->line, 0, i);
	tmp3 = ft_substr(shell->line, j, ft_strlen(shell->line) - j + 1);
	free(shell->line);
	shell->line = ft_strjoin(tmp2, tmp);
	free(tmp2);
	tmp2 = shell->line;
	shell->line = ft_strjoin(shell->line, tmp3);
	free(tmp2);
	free(tmp3);
	return (1);
}


void	trim_line(t_shell *shell)
{
	char	*tmp;

	tmp = shell->line;
	shell->line = ft_strtrim(shell->line, SPACES);
	free(tmp);
	shell->es = shell->line + ft_strlen(shell->line);
	while (shell->line < shell->es)
	{
		if (*shell->line == '\'' || *shell->line == '\"')
		{
			shell->es = ft_strchr(shell->line + 1, *shell->line);
			if (!shell->es)
				shell->es = shell->line + ft_strlen(shell->line);
			shell->line++;
		}
		else if (*shell->line == '\\')
		{
			shell->line++;
			if (*shell->line == '\0')
				break ;
		}
		else if (*shell->line == '$')
		{
			if (point_to_expand(shell->line - shell->line, shell->line, shell))
				continue ;
		}
		shell->line++;
	}
}
