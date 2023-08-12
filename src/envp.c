/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:23:47 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/12 02:14:40 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_envp(t_shell *shell)
{
	t_env	*tmp;
	t_env	*max;
	char	*max_key;
	int		i;

	i = shell->envp_size;
	while (i--)
	{
		tmp = shell->env;
		max = NULL;
		max_key = "";
		while (tmp)
		{
			if (ft_strcmp(tmp->key, max_key) > 0 && tmp->index == 0)
			{
				max = tmp;
				max_key = tmp->key;
			}
			tmp = tmp->next;
		}
		if (max)
			max->index = i + 1;
	}
}

void	envp_destroy(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

char	*get_env(char *key, t_shell *shell)
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

t_env	*add_env(t_shell *shell, char *key, char *value)
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
	new->next = NULL;
	if (!shell->env)
		return (new);
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (shell->env);
}

void	envp_to_list(char **envp, t_shell *shell)
{
	int		i;
	char	**split;

	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (split && split[0] && split[1])
			shell->env = add_env(shell, split[0], split[1]);
		ft_free_array(split);
		i++;
	}
	sort_envp(shell);
}
