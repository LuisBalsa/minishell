/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:23:47 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/08 21:09:43 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

t_env	*add_env(t_env *env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!env)
		return (new);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

void	envp_to_list(char **envp, t_env **env)
{
	int		i;
	char	**split;

	*env = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (split && split[0] && split[1])
			*env = add_env(*env, split[0], split[1]);
		ft_free_array(split);
		i++;
	}
}
