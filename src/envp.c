/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:23:47 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/28 11:17:56 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_envp(t_shell *shell)
{
	t_env	*tmp;
	char	*env;
	int		i;

	if (shell->envp)
		ft_free_array(shell->envp);
	if (!shell->env)
	{
		shell->envp = NULL;
		return ;
	}
	shell->envp = ft_calloc(shell->envp_size, sizeof(char *));
	tmp = shell->env;
	i = 0;
	while (tmp)
	{
		if (tmp->visible)
		{
			env = ft_strjoin(tmp->key, "=");
			shell->envp[i++] = ft_strjoin(env, tmp->value);
			free(env);
		}
		tmp = tmp->next;
	}
	shell->envp[i] = NULL;
}

void	print_envp(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->visible)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	zero_index(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
}

void	sort_envp(t_shell *shell)
{
	t_env	*tmp;
	t_env	*max;
	char	*max_key;
	int		i;

	zero_index(shell);
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

t_env	*add_env(t_shell *shell, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	shell->envp_size++;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->index = 0;
	new->visible = visible;
	new->next = NULL;
	if (!shell->env)
		return (new);
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	sort_envp(shell);
	update_envp(shell);
	return (shell->env);
}

void	rm_env(char *key, t_shell *shell)
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
			sort_envp(shell);
			update_envp(shell);
			return ;
		}
		tmp_last = tmp;
		tmp = tmp->next;
	}
}

void	envp_to_list(char **envp, t_shell *shell)
{
	int		i;
	char	**split;
	char	*value;

	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (ft_strchr(envp[i], '='))
			value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		else
			value = NULL;
		if (split && split[0])
			shell->env = add_env(shell, split[0], value, 1);
		ft_free_array(split);
		if (value)
			free (value);
		i++;
	}
	sort_envp(shell);
}
