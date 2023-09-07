/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:05:42 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/07 13:02:30 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*path_slash(char *cdpath, char **path)
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

static bool	cdpath_try(t_shell *shell, char **cdpath, char *path, int index)
{
	char	*tmp;
	char	*tmp_path;

	tmp_path = path_slash(cdpath[index], &path);
	tmp = ft_strjoin(cdpath[index], tmp_path);
	free(tmp_path);
	if (ms_chdir(shell, tmp))
	{
		tmp[ft_strlen(tmp) - 1] = '\0';
		ft_putendl_fd(tmp, STDOUT_FILENO);
		ft_free_array(cdpath);
		free(tmp);
		return (true);
	}
	free(tmp);
	return (false);
}

static bool	cdpath(t_shell *shell, char *path)
{
	char	**cdpath;
	int		i;

	if (!env_get("CDPATH", shell) || path[0] == '/')
		return (false);
	cdpath = ft_split(env_get("CDPATH", shell), ':');
	i = 0;
	while (cdpath[i])
	{
		if (cdpath_try(shell, cdpath, path, i++))
			return (true);
	}
	ft_free_array(cdpath);
	return (false);
}

static void	hyphen_cd_print(t_shell *shell, char *pwd)
{
	char	*str;

	if (pwd[0] != '~')
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
	{
		str = ft_strjoin(env_get("HOME", shell), &pwd[1]);
		ft_putendl_fd(str, STDOUT_FILENO);
		free(str);
	}
}

void	ms_cd(t_shell *shell, t_exec *cmd)
{
	if (!cmd->argv[1])
	{
		if (!ms_chdir(shell, env_get("HOME", shell)))
			print_error(shell, "cd", "HOME not set", 1);
	}
	else
	{
		if (cmd->argv[2])
			print_error(shell, "cd", "too many arguments", 1);
		else if (ft_strcmp(cmd->argv[1], "-") == 0)
		{
			if (!ms_chdir(shell, env_get("OLDPWD", shell)))
			{
				print_error(shell, "cd", "OLDPWD not set", 1);
				return ;
			}
			hyphen_cd_print(shell, env_get("PWD", shell));
		}
		else if (cmd->argv[1][0]
			&& !ms_chdir(shell, cmd->argv[1]) && !cdpath(shell, cmd->argv[1]))
			print_error(shell, "cd: no such file or directory",
				cmd->argv[1], 1);
	}
}
