/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:22 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/18 22:51:20 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//General function in Adam's Libft
int	ft_contains_only(char *str, char *characters)
{
	while (*str)
	{
		if (!ft_strchr(characters, *str++))
			return (0);
	}
	return (1);
}

int	echo_flag(t_exec exec, int *arg)
{
	int	flag;

	flag = 0;
	while (exec.argv[++*arg])
	{
		if (exec.argv[*arg][0] == '-')
		{
			if (ft_contains_only(&exec.argv[*arg][1], "n"))
				flag = 1;
			else
				break ;
		}
		else
			break ;
	}
	return (flag);
}

void	ms_echo(t_exec exec)
{
	int	i;
	int	flag;

	i = 0;
	flag = echo_flag(exec, &i);
	if (exec.argv[i])
	{
		ft_putstr_fd(exec.argv[i], STDOUT_FILENO);
		while (exec.argv[++i])
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(exec.argv[i], STDOUT_FILENO);
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
/*
//cc -o echo echo.c ../Libft_obj/libft.a -g
int	main(int argc, char **argv)
{
	t_exec	exec;
	int		i = 0;
	int		j = 1;

	(void)argc;
	exec.argv[i] = "echo";
	while (argv[j])
		exec.argv[++i] = argv[j++];
	exec.argv[i + 1] = 0;
	ms_echo(exec);
	return (0);
}*/
