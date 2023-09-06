/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:57:30 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/06 01:50:46 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_envp_sorted(t_shell *shell, int export)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->env;
	while (i++ < shell->envp_size)
	{
		while (tmp)
		{
			if (tmp->index == i)
			{
				if (export && tmp->visible)
					ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else if (export && !tmp->visible)
					ft_printf("declare -x %s\n", tmp->key);
				else if (!export && tmp->visible)
					ft_printf("%s=\"%s\"\n", tmp->key, tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		tmp = shell->env;
	}
}

static bool	valid_var(t_shell *shell, char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		print_error(shell, arg, "not a valid identifier", 1);
		return (false);
	}
	while (arg[++i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_error(shell, arg, "not a valid identifier", 1);
			return (false);
		}
	}
	return (true);
}

void	ms_export(t_shell *shell, t_exec *cmd)
{
	int		i;
	char	*value;
	char	**split;

	if (!cmd->argv[1])
		print_envp_sorted(shell, 1);
	else
	{
		i = 0;
		while (cmd->argv[++i])
		{
			if (!valid_var(shell, cmd->argv[i]))
				continue ;
			if (ft_strchr(cmd->argv[i], '='))
			{
				split = ft_split(cmd->argv[i], '=');
				value = ft_strdup(ft_strchr(cmd->argv[i], '=') + 1);
				export_env(shell, split[0], value, 1);
				ft_free_array(split);
				free(value);
			}
			else
				export_env(shell, cmd->argv[i], "", 0);
		}
	}
}
/*
 static void	init_shell(t_shell *shell, char **envp)
{
	[>g_exit = 0;<]
	shell->cmd = NULL;
	shell->line = NULL;
	shell->envp_size = 0;
	envp_to_list(envp, shell);
}

[>cc -o export export.c ../envp.c ../libft_obj/libft.a -g<]
int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_exec	cmd;
	int		i = 0;
	int		j = 1;

	(void)argc;
	init_shell(&shell, envp);
	cmd.argv[i] = "export";
	while (argv[j])
		cmd.argv[++i] = argv[j++];
	cmd.argv[i + 1] = NULL;
	printf("ENV:\n");
	print_envp(&shell);
	printf("\n---------------------\nrunning export...\n");
	ms_export(&shell, &cmd);
	printf("\n---------------------\nNEW ENV:\n");
	print_envp(&shell);
	envp_destroy(shell.env);
	return (0);
} */
