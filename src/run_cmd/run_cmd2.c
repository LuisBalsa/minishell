/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:29:10 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/07 13:13:12 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin(char *argv)
{
	if (!ft_strcmp(argv, "echo")
		|| !ft_strcmp(argv, "cd")
		|| !ft_strcmp(argv, "pwd")
		|| !ft_strcmp(argv, "export")
		|| !ft_strcmp(argv, "unset")
		|| !ft_strcmp(argv, "env")
		|| !ft_strcmp(argv, "exit"))
		return (1);
	return (0);
}

static void	check_execve(t_shell *shell, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (!access(path, F_OK) && access(path, X_OK))
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (!access(path, F_OK))
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else if (ft_strchr(path, '/'))
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else
		ft_putendl_fd(": command not found", STDERR_FILENO);
	g_exit = 127
		- ((!access(path, F_OK) && access(path, X_OK)) || !access(path, F_OK));
	free(path);
	free_exit(shell);
}

static char	*get_path(t_shell *shell, char *cmd)
{
	int		i;
	char	*path;
	char	*path2;
	char	**paths;

	i = 0;
	path = NULL;
	path2 = NULL;
	if (ft_strchr(cmd, '/') || !env_get("PATH", shell) || !ft_strcmp(cmd, ""))
		return (ft_strdup(cmd));
	paths = ft_split(env_get("PATH", shell), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path2 = ft_strjoin(path, cmd);
		free(path);
		path = NULL;
		if (!access(path2, F_OK))
			return (path2);
		free(path2);
		path2 = NULL;
		i++;
	}
	ft_free_array(paths);
	return (ft_strdup(cmd));
}

static void	check_exit_status(void)
{
	if (g_exit == 11 || g_exit == 139)
		ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
	else if (g_exit == 8 || g_exit == 136)
		ft_putendl_fd("Floating point exception (core dumped)", STDERR_FILENO);
}

void	run_exec(t_shell *shell, t_exec *cmd)
{
	pid_t	pid;
	char	*path;

	if (!cmd->argv[0])
		return ;
	if (!is_builtin(cmd->argv[0]))
	{
		sig_handler(SIGCHILD);
		pid = check_fork();
		if (pid == 0)
		{
			path = get_path(shell, cmd->argv[0]);
			execve(path, cmd->argv, shell->envp);
			check_execve(shell, path);
		}
		waitpid(pid, &g_exit, 0);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		else if (WIFSIGNALED(g_exit))
			g_exit = 128 + WTERMSIG(g_exit);
		check_exit_status();
		sig_handler(SIGRESTORE);
	}
	else
		run_builtin(shell, cmd);
}
