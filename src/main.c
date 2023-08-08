/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:12:03 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/08 13:52:06 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

char	*get_prompt(void)
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

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	not_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	init_shell(t_shell *shell, char **envp)
{
	envp_to_list(envp, &shell->env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*prompt;

	(void)argc;
	(void)argv;
	g_exit = 0;
	init_shell(&shell, envp);
	while (1)
	{
		prompt = get_prompt();
		shell.line = readline(prompt);
		free(prompt);
		if (!shell.line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (not_only_spaces(shell.line))
		{
			add_history(shell.line);
		}
		free(shell.line);
	}
	envp_destroy(shell.env);
	return (0);
}
