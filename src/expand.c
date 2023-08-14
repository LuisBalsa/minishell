/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:13:24 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/13 13:17:46 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand(char *key, int i, int j, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(shell->line, 0, i);
	tmp2 = ft_substr(shell->line, j, ft_strlen(shell->line) - j + 1);
	tmp3 = shell->line;
	free(tmp3);
	shell->line = ft_strjoin(tmp, key);
	free(tmp);
	tmp = shell->line;
	shell->line = ft_strjoin(shell->line, tmp2);
	free(tmp);
	free(tmp2);
	return (1);
}

int	expand_free(char *key, int i, int j, t_shell *shell)
{
	expand(key, i, j, shell);
	free(key);
	return (1);
}
