/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:30:53 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/04 18:32:49 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Add errors from original functions
void	ms_pwd(t_shell *shell, t_exec *cmd)
{
	char	*path;

	if (cmd->argv[1] && cmd->argv[1][0] == '-')
	{
		print_error(shell, cmd->argv[0], "flags not supported", 2);
		return ;
	}
	path = getcwd(NULL, 0);
	if (!path)
		print_error(shell, cmd->argv[0], "couldn't get current directory", 2);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
}
/*
//cc -o pwd pwd.c ../Libft_obj/libft.a -g
int	main(int argc, char **argv)
{
	t_exec	cmd;
	int		i = 0;
	int		j = 1;

	(void)argc;
	cmd.argv[i] = "pwd";
	while (argv[j])
		cmd.argv[++i] = argv[j++];
	cmd.argv[i + 1] = 0;
	ms_pwd(&cmd);
	return (0);
}*/
