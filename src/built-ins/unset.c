/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:58:46 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/12 15:02:22 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	valid_unset_var(t_shell *shell, char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (error_inside(shell, "unset: ", arg, 1));
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (error_inside(shell, "unset: ", arg, 1));
	}
	return (true);
}

char	*get_key(char *key, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ms_unset(t_shell *shell, t_exec *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (*cmd->argv[i] && valid_unset_var(shell, cmd->argv[i]))
		{
			if (get_key(cmd->argv[i], shell))
				env_rm(cmd->argv[i], shell);
		}
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}
