/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:23:47 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/07 13:40:30 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	envp_update(t_shell *shell)
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
	shell->envp = ft_calloc(shell->envp_size + 1, sizeof(char *));
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
}

void	envp_print(t_shell *shell)
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

void	envp_sort(t_shell *shell)
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
			shell->env = env_add(shell, split[0], value, 1);
		ft_free_array(split);
		if (value)
			free (value);
		i++;
	}
	envp_sort(shell);
}
