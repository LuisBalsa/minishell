/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:05:42 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/16 13:19:38 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
#include <stdbool.h>

bool	equal_str(const char *s1, const char *s2)
{
	if (ft_strcmp(s1, s2) == 0)
		return (true);
	else
		return (false);
}

char	*env_find_value(t_env *env, char *target)
{
	t_env	*tmp;
	
	tmp = env;
	while (tmp)
	{
		if (equal_str(target, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

bool	env_change_value(t_env *env, char *target, char *new_value)
{
	t_env	*tmp;
	
	tmp = env;
	while (tmp)
	{
		if (equal_str(target, tmp->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	ms_cd(t_shell *shell, t_exec *exec)
{
	char	*pwd;
	char	*curpath;

	pwd = getcwd(NULL, 0);
	printf("Last dir is %s\n", pwd);
	free(pwd);
	if (!exec->argv[1])
		chdir(env_find_value(shell->env, "HOME"));
	pwd = getcwd(NULL, 0);
	printf("New dir is %s\n", pwd);
	free(pwd);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->cmd = NULL;
	shell->line = NULL;
	shell->envp_size = 0;
	envp_to_list(envp, shell);
}

//cc -o cd cd.c ../envp.c ../Libft_obj/libft.a -g
int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_exec	exec;
	int		i = 0;
	int		j = 1;
	
	(void)argc;
	init_shell(&shell, envp);
	exec.argv[i] = "pwd";
	while (argv[j])
		exec.argv[++i] = argv[j++];
	exec.argv[i + 1] = 0;
	ms_cd(&shell, &exec);
	return (0);
}
