/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:17:20 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/12 00:00:40 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	trim_arg(char *arg)
{
	int		squote;
	int		dquote;

	dquote = 0;
	squote = 0;
	while (*arg)
	{
		if (*arg == '"' && !squote)
			dquote = !dquote;
		if (*arg == '\'' && !dquote)
			squote = !squote;
		if (ft_strchr(SPACES, *arg) && !squote && !dquote)
			*arg = '\0';
		arg++;
	}
}

void	trim_quotes(char *arg, int *len)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < *len)
	{
		if ((arg[i] == '"' || arg[i] == '\'') && !quote)
		{
			quote = arg[i];
			memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else if (quote && arg[i] == quote)
		{
			quote = 0;
			memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else
			i++;
	}
}
