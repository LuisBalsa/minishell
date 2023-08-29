/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:22 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/29 12:22:15 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_contains_only(char *str, char *characters)
{
	while (*str)
	{
		if (!ft_strchr(characters, *str++))
			return (0);
	}
	return (1);
}

static int	echo_flag(t_exec *cmd, int *arg_index)
{
	int	flag;

	flag = 0;
	while (cmd->argv[++*arg_index])
	{
		if (cmd->argv[*arg_index][0] == '-')
		{
			if (ft_contains_only(&cmd->argv[*arg_index][1], "n"))
				flag = 1;
			else
				break ;
		}
		else
			break ;
	}
	return (flag);
}

void	ms_echo(t_exec *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = echo_flag(cmd, &i);
	if (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		while (cmd->argv[++i])
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
/*
//cc -o echo echo.c ../Libft_obj/libft.a -g
int	main(int argc, char **argv)
{
	t_exec	cmd;
	int		i = 0;
	int		j = 1;

	(void)argc;
	cmd.argv[i] = "echo";
	while (argv[j])
		cmd.argv[++i] = argv[j++];
	cmd.argv[i + 1] = 0;
	ms_echo(cmd);
	return (0);
}*/
