/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:12:03 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/06 00:19:32 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

static char	*get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin(PROMPT_BEGIN, cwd);
	free(cwd);
	cwd = ft_strjoin(prompt, PROMPT_END);
	free(prompt);
	return (cwd);
}

void	wait_children(t_shell *shell)
{
	if (waitpid(shell->pid, &g_exit, 0) != -1)
	{
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		else if (WIFSIGNALED(g_exit))
			g_exit = WTERMSIG(g_exit) + 128;
	}
	while (wait(0) != -1)
		;
	if (g_exit == 130)
		shell->status = RESTORE;
}

static int	run_command_line(t_shell *shell)
{
	sig_handler(SIGRESTORE);
	shell->status = STOP;
	shell->prompt = get_prompt();
	shell->line = readline(shell->prompt);
	free(shell->prompt);
	if (!shell->line)
		g_exit = 0;
	if (shell->line && init_line(shell) && expand_line(shell))
	{
		trim_line(shell);
		if (parser(shell) && shell->status == CONTINUE)
		{
			sig_handler(SIGPIPE);
			run_cmd(shell, shell->cmd);
		}
		free_cmd(shell->cmd);
	}
	free(shell->line);
	return (shell->status);
}

static void	init_shell(t_shell *shell, char **envp)
{
	g_exit = 0;
	shell->cmd = NULL;
	shell->line = NULL;
	shell->envp = NULL;
	shell->envp_size = 0;
	envp_to_list(envp, shell);
	update_envp(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (run_command_line(&shell))
		;
	clear_history();
	envp_destroy(shell.env);
	if (shell.envp)
		ft_free_array(shell.envp);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	return (g_exit);
}
