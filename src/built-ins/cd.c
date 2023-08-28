/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:05:42 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/28 10:51:33 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

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

	tmp_pwd = getcwd(NULL, 0);
	tmp_path = ft_strdup(path);
	if (chdir(path) != 0)
	{
		free(tmp_pwd);
		free(tmp_path);
		return (false);
	}
	env_change(shell, "OLDPWD", tmp_pwd);
	env_change(shell, "PWD", tmp_path);
	return (true);
}

void	path_slash(char *cdpath, char **path)
{
	char	*tmp;

	if (cdpath[ft_strlen(cdpath) - 1] != '/')
	{
		if (*path[0] != '/')
		{
			tmp = ft_strjoin("/", *path);
			free(*path);
			*path = tmp;
		}
		else 
			return ;
	}
	else 
	{
		if (*path[0] == '/')
		{
			tmp = ft_strdup(*path + 1);
			free(*path);
			*path = tmp;
		}
		else 
			return ;
	}
}

bool	cdpath(t_shell *shell, char *path)
{
	char	**cdpath;
	char	*tmp;
	int		i;
	
	if (!get_env("CDPATH", shell) || path[0] == '/')
		return (false);
	cdpath = ft_split(get_env("CDPATH", shell), ':');
	i = 0;
	while (cdpath[i])
	{
		path_slash(cdpath[i], &path);
		tmp = ft_strjoin(cdpath[i++], path);
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

void	hyphen_cd_print(t_shell *shell, char *pwd)
{
	char	*str;

	if (pwd[0] != '~')
		ft_putstr_fd(pwd, STDOUT_FILENO);
	else
	{
		str = ft_strjoin(get_env("HOME", shell), &pwd[1]);
		ft_putstr_fd(str, STDOUT_FILENO);
		free(str);
	};
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
			hyphen_cd_print(shell, get_env("PWD", shell));
		}
		else if (!ms_chdir(shell, cmd->argv[1]) && !cdpath(shell, cmd->argv[1]))
		{
			err = ft_strjoin("cd: no such file or directory: ", cmd->argv[1]);
			ft_putstr_fd(err, STDERR_FILENO);
			free(err);
		}
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	/*printf("New dir is %s\n", get_env("PWD", shell));
	printf("OLDPWD is %s\n", get_env("OLDPWD", shell));*/
}

/*void	ms_cd(t_shell *shell, t_exec *cmd)
{
	char	*err;
	
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
	shell->envp = NULL;
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
	char	*cdpath = ft_strdup("~");
	
	(void)argc;
	init_shell(&shell, envp);
	env_change(&shell, "CDPATH", cdpath);
	cmd.argv[i] = "pwd";
	while (argv[j])
		cmd.argv[++i] = argv[j++];
	cmd.argv[i + 1] = 0;
	ms_cd(&shell, &cmd);
	envp_destroy(shell.env);
	free(cdpath);
	return (0);
}
