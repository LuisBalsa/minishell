/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:48:06 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/19 19:35:02 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (ft_strchr(SPACES, *tmp) && !squote && !dquote)
			*tmp = '\0';
		tmp++;
	}
}

void	trim_line(t_shell *shell)
{
	trim_spaces(shell->line);
}
