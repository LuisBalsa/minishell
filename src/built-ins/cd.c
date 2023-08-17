/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:05:42 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/17 11:56:31 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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

bool	env_change(t_shell *shell, char *target, char *new_value)
{
	t_env	*tmp;
	
	tmp = shell->env;
	while (tmp)
	{
		if (equal_str(target, tmp->key))
		{
			free(tmp->value);
			tmp->value = new_value;
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	ms_chdir(t_shell *shell, char *path)
{
	char	*tmp_pwd;
	char	*tmp_path;

	if (chdir(path) != 0)
		return (false);
	tmp_pwd = getcwd(NULL, 0);
	tmp_path = ft_strdup(path);
	env_change(shell, "OLDPWD", tmp_pwd);
	env_change(shell, "PWD", tmp_path);
	return (true);
}

bool	cdpath(t_shell *shell, char *path)
{
	char	**cdpath;
	char	*tmp;
	
	if (!get_env("CDPATH", shell))
		return (false);
	cdpath = ft_split(get_env("CDPATH", shell), ':');
	while (*cdpath)
	{
		tmp = ft_strjoin(*cdpath++, path);
		if (ms_chdir(shell, tmp))
		{
			ft_free_array(cdpath);
			free(tmp);
			return (true);
		}
		free(tmp);
	}
	ft_free_array(cdpath);
	return (false);
}

void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*err;
	
	if (cmd->argv[2])
		ft_putstr_fd("cd: too many arguments", STDERR_FILENO);
	if (!cmd->argv[1])
	{
		if (!ms_chdir(shell, env_find_value(shell->env, "HOME")))
			ft_putstr_fd("cd: HOME variable", STDERR_FILENO);
	}
	else 
	{
		if (equal_str(cmd->argv[1], "-"))
		{
			if (!ms_chdir(shell, get_env("OLDPWD", shell)))
				ft_putstr_fd("cd: OLDPWD variable", STDERR_FILENO);
			ft_putstr_fd(get_env("PWD", shell), STDOUT_FILENO);
		}
		else if (!ms_chdir(shell, cmd->argv[1]) && !cdpath(shell, cmd->argv[1]))
		{
			err = ft_strjoin("cd: no such file or directory: ", cmd->argv[1]);
			ft_putstr_fd(err, STDERR_FILENO);
			free(err);
		}
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	printf("New dir is %s\n", get_env("PWD", shell));
	printf("OLDPWD is %s\n", get_env("OLDPWD", shell));
}

/*void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*err;
	char	**cdpath;
	
	if (cmd->argv[2])
		print_error(shell, "cd: too many arguments", 2);
	if (!cmd->argv[1])
	{
		if (!ms_chdir(shell, env_find_value(shell->env, "HOME")))
			print_error(shell, "cd: HOME variable", 2);
	}
	else 
	{
		if (equal_str(cmd->argv[1], "-"))
		{
			if (!ms_chdir(shell, get_env("OLDPWD", shell)))
				print_error(shell, "cd: OLDPWD variable", 2);
			ft_putstr_fd(get_env("PWD", shell), STDOUT_FILENO);
		}
		else if (!ms_chdir(shell, cmd->argv[1]) && !cdpath(shell, cmd->argv[1]))
		{
			err = ft_strjoin("cd: no such file or directory: ", cmd->argv[1]);
			print_error(shell, err, 2);
			free(err);
		}
	}
}*/

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
	t_exec	cmd;
	int		i = 0;
	int		j = 1;
	
	(void)argc;
	init_shell(&shell, envp);
	cmd.argv[i] = "pwd";
	while (argv[j])
		cmd.argv[++i] = argv[j++];
	cmd.argv[i + 1] = 0;
	ms_cd(&shell, &cmd);
	envp_destroy(shell.env);
	return (0);
}
