/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:15:18 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/10 13:26:07 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// por usar:
void	check(int result, char *msg, t_shell *shell)
{
	if (result == -1)
	{
		ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
		perror(msg);
		g_exit = EXIT_FAILURE;
		shell->status = STOP;
	}
}

int	print_error(char *msg, int exit)
{
	ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_exit = exit;
	return (1);
}
