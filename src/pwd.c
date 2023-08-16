/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:30:53 by achien-k          #+#    #+#             */
/*   Updated: 2023/08/16 12:04:27 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Add errors from original functions
void	ms_pwd(t_exec *exec)
{
	char	*path;

	if (exec->argv[1])
	{
		if (exec->argv[1][0] == '-')
			ft_putstr_fd("pwd: flags not supported", STDERR_FILENO);
		else
			ft_putstr_fd("pwd: too many arguments", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return ;
	}
	path = getcwd(NULL, 0);
	if (!path)
		ft_putstr_fd("pwd: couldn't retrieve current directory", 2);
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(path);
}
/*
//cc -o pwd pwd.c ../Libft_obj/libft.a -g
int	main(int argc, char **argv)
{
	t_exec	exec;
	int		i = 0;
	int		j = 1;
	
	(void)argc;
	exec.argv[i] = "pwd";
	while (argv[j])
		exec.argv[++i] = argv[j++];
	exec.argv[i + 1] = 0;
	ms_pwd(&exec);
	return (0);
}*/
