/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:04:28 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/01 14:47:04 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_back_slash(int sig)
{
	if (sig == SIGINT)
		;
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
}


static void	sigrestore(int sig)
{
	(void)sig;
	g_exit = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_forced_update_display();
}

static void	sig_here_doc(int sig)
{
	if (sig != SIGINT)
		return ;
	exit(130);
}

static void	sigint_ignore(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		ft_putstr_fd("\n", 2);
		signal(SIGINT, SIG_IGN);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGRESTORE)
	{
		signal(SIGINT, sigrestore);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == SIGHEREDOC)
	{
		signal(SIGINT, sig_here_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == SIGCHILD)
	{
		signal(SIGINT, sig_back_slash);
		signal(SIGQUIT, sig_back_slash);
	}
	if (sig == SIGPIPE)
	{
		signal(SIGINT, sigint_ignore);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == SIGIGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
