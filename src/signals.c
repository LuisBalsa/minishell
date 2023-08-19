/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:04:28 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/20 00:28:59 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_here_doc(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_printf("\n");
	g_exit = 130;
	exit(g_exit);
}

static void	sig_back_slash(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)\n", 1);
	g_exit = 128 + sig - (sig == SIGQUIT);
	ft_putstr_fd("\n", 2);
//	exit(g_exit);
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
	if (sig == SIGIGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
