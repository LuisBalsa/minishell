/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achien-k <achien-k@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:46:43 by achien-k          #+#    #+#             */
/*   Updated: 2023/09/07 13:05:22 by achien-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ms_chdir(t_shell *shell, char *path)
{
	char	*tmp_pwd;

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
