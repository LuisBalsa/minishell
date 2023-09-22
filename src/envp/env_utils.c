/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:52:26 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/12 11:43:49 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_get(char *key, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*env_add(t_shell *shell, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	shell->envp_size++;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->index = 0;
	new->visible = visible;
	new->next = NULL;
	if (!shell->env)
		return (new);
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	envp_sort(shell);
	envp_update(shell);
	return (shell->env);
}

bool	env_mod(t_shell *shell, char *target, char *new_value)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(target, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			tmp->visible = 1;
			envp_update(shell);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	env_export(t_shell *shell, char *key, char *value, int visible)
{
	if (env_get(key, shell) && visible)
		env_mod(shell, key, value);
	else if (!env_get(key, shell))
		env_add(shell, key, value, visible);
}

bool	env_rm(char *key, t_shell *shell)
{
	t_env	*tmp;
	t_env	*tmp_last;

	tmp = shell->env;
	tmp_last = tmp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp_last->next = tmp->next;
			if (tmp == shell->env)
				shell->env = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			shell->envp_size--;
			envp_sort(shell);
			envp_update(shell);
			return (true);
		}
		tmp_last = tmp;
		tmp = tmp->next;
	}
	return (false);
}
