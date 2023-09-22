/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:46:43 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/13 11:58:31 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

bool	ms_chdir(t_shell *shell, char *path)
{
	char	*tmp_pwd;

	if (!path)
		return (false);
	tmp_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(tmp_pwd);
		return (false);
	}
	env_export(shell, "OLDPWD", tmp_pwd, 1);
	free(tmp_pwd);
	tmp_pwd = getcwd(NULL, 0);
	env_export(shell, "PWD", tmp_pwd, 1);
	free(tmp_pwd);
	return (true);
}
