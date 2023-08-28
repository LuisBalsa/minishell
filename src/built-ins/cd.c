/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:05:42 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/28 12:58:37 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	env_change(t_shell *shell, char *target, char *new_value)
{
	t_env	*tmp;
	
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(target, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	ms_chdir(t_shell *shell, char *path)
{
	char	*tmp_pwd;

	tmp_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(tmp_pwd);
		return (false);
	}
	env_change(shell, "OLDPWD", tmp_pwd);
	free(tmp_pwd);
	tmp_pwd = getcwd(NULL, 0);
	env_change(shell, "PWD", tmp_pwd);
	free(tmp_pwd);
	return (true);
}

char	*path_slash(char *cdpath, char **path)
{
	char	*tmp;

	if (cdpath[ft_strlen(cdpath) - 1] != '/')
	{
		if (*path[0] != '/')
		{
			tmp = ft_strjoin("/", *path);
			return (tmp);
		}
		else 
			return (ft_strdup(cdpath));
	}
	else 
	{
		if (*path[0] == '/')
		{
			tmp = ft_strdup(*path + 1);
			return (tmp);
		}
		else 
			return (ft_strdup(cdpath));
	}
}

bool	cdpath(t_shell *shell, char *path)
{
	char	**cdpath;
	char	*tmp;
	char	*tmp_path;
	int		i;
	
	if (!get_env("CDPATH", shell) || path[0] == '/')
		return (false);
	cdpath = ft_split(get_env("CDPATH", shell), ':');
	i = 0;
	while (cdpath[i])
	{
		tmp_path = path_slash(cdpath[i++], &path);
		tmp = ft_strjoin(tmp_path, path);
		if (ms_chdir(shell, tmp))
		{
			ft_free_array(cdpath);
			free(tmp);
			return (true);
		}
		free(tmp);
		free(tmp_path);
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
	if (!cmd->argv[1])
	{
		if (!ms_chdir(shell, get_env("HOME", shell)))
			print_error(shell, "cd", "HOME variable", 2);
	}
	else 
	{
		if (cmd->argv[2])
			print_error(shell, "cd", "too many arguments", 2);
		else if (ft_strcmp(cmd->argv[1], "-") == 0)
		{
			if (!ms_chdir(shell, get_env("OLDPWD", shell)))
				print_error(shell, "cd", "OLDPWD variable", 2);
			hyphen_cd_print(shell, get_env("PWD", shell));
		}
		else if (!ms_chdir(shell, cmd->argv[1]) && !cdpath(shell, cmd->argv[1]))
			print_error(shell, "cd: no such file or directory", cmd->argv[1], 2);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/*static void	ms_cd_test(t_shell *shell, t_exec *cmd)
{
	char	*err;
	
	if (!cmd->argv[1])
	{
		if (!ms_chdir(shell, get_env("HOME", shell)))
			ft_putstr_fd("cd: HOME variable", STDERR_FILENO);
	}
	else 
	{
		if (cmd->argv[2])
			ft_putstr_fd("cd: too many arguments", STDERR_FILENO);
		else if (ft_strcmp(cmd->argv[1], "-") == 0)
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
	printf("Moved from\n%s\nto\n%s\n", get_env("OLDPWD", shell), get_env("PWD", shell));
}

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
	cmd.argv[i] = ft_strdup("pwd");
	while (argv[j])
		cmd.argv[++i] = ft_strdup(argv[j++]);
	cmd.argv[i + 1] = 0;
	ms_cd_test(&shell, &cmd);
	envp_destroy(shell.env);
	i = 0;
	while (cmd.argv[i])
		free(cmd.argv[i++]);
	ft_free_array(shell.envp);
	free(cdpath);
	return (0);
}*/
