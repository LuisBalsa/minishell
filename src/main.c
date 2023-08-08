/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:12:03 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/08 17:27:12 by luide-so         ###   ########.fr       */
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

static int	not_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	run_comand_line(t_shell *shell)
{
	shell->prompt = get_prompt();
	shell->line = readline(shell->prompt);
	free(shell->prompt);
	if (!shell->line)
		shell->status = 0;
	if (not_only_spaces(shell->line))
	{
		add_history(shell->line);
/* 		parse(shell);
		run_cmd(shell);
		free_cmd(shell->cmd); */
	}
	free(shell->line);
	return (shell->status);
}

static void	init_shell(t_shell *shell, char **envp)
{
	g_exit = 0;
	shell->status = 1;
	envp_to_list(envp, &shell->env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	print_shell_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	print_shell_env(shell.env);
	while (run_comand_line(&shell))
		;
	rl_clear_history();
	envp_destroy(shell.env);
	ft_putendl_fd("exit", 1);
	return (g_exit);
}
