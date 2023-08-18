/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:12:03 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/18 00:47:28 by luide-so         ###   ########.fr       */
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

static int	run_command_line(t_shell *shell)
{
	shell->status = STOP;
	shell->prompt = get_prompt();
	shell->line = readline(shell->prompt);
	rl_set_prompt(shell->prompt);
	free(shell->prompt);
	if (!shell->line)
		g_exit = 0;
	if (shell->line && init_line(shell) && expand_line(shell))
	{
		trim_line(shell);
		if (parser(shell) && shell->status == CONTINUE)
			run_cmd(shell, shell->cmd);
		free_cmd(shell->cmd);
	}
	free(shell->line);
	return (shell->status);
}

static void	print_envp_sorted(t_shell *shell)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->env;
	while (i < shell->envp_size)
	{
		while (tmp)
		{
			if (tmp->index == i)
			{
				ft_printf("%s=%s\n", tmp->key, tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		tmp = shell->env;
		i++;
	}
}

static void	init_shell(t_shell *shell, char **envp)
{
	g_exit = 0;
	shell->cmd = NULL;
	shell->line = NULL;
	shell->envp_size = 0;
	envp_to_list(envp, shell);
	sig_handler(SIGRESTORE);
	print_envp_sorted(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (run_command_line(&shell))
		;
	rl_clear_history();
	envp_destroy(shell.env);
	ft_putendl_fd("exit", 1);
	return (g_exit);
}
