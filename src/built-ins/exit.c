/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:21:23 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/30 11:55:50 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (false);
	}
	return (true);
}

static bool islonglong(char *str)
{
	int	is_negative;
	int len;

	if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	while (*str == '0')
		str++;
	if (!isnumber(str))
		return (false);
	len = ft_strlen(str);
	if (len > 19)
		return (false);
	if (is_negative)
		return (ft_strncmp(str, "9223372036854775808", len) <= 0);
	else
		return (ft_strncmp(str, "9223372036854775807", len) <= 0);
}

void	ms_exit(t_shell *shell, t_exec *cmd)
{
	char	*err;

	err = NULL;
	if (cmd->argv[1])
	{
		if (!islonglong(cmd->argv[1]))
		{
			err = ft_strjoin(cmd->argv[1], ": numeric argument required");
			print_error(shell, cmd->argv[0], err, 2);
			free(err);
		}
		else
			g_exit = ft_atoi(cmd->argv[1]) % 256;
	}
	shell->status = STOP;
}
