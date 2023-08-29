/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:21:23 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/29 12:58:22 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_exit(t_shell *shell, t_exec *cmd)
{
	char	*err;
	int		i;

	err = NULL;
	i = 0;
	if (cmd->argv[1])
	{
		while (cmd->argv[1][i])
		{
			if (!ft_isdigit(cmd->argv[1][i++]))
			{
				err = ft_strjoin(cmd->argv[1], ": numeric argument required");
				print_error(shell, cmd->argv[0], err, 2);
				break ;
			}
		}
		if (err)
			free(err);
		else
			g_exit = ft_atoi(cmd->argv[1]) % 255;
	}
	shell->status = STOP;
}
