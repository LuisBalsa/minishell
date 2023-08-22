
#include "../../include/minishell.h"
#include <stdio.h>

// first two functions should be in a different file, as they are used by cd
bool	equal_str(const char *s1, const char *s2)
{
	if (ft_strcmp(s1, s2) == 0)
		return (true);
	else
		return (false);
}

bool	change_env(t_shell *shell, char *key, char *value)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (equal_str(key, tmp->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

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
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_error(shell, arg, ": not a valid identifier", 2);
			return (false);
		}
		i++;
		if (arg[i] == '=')
			break ;
	}
	return (true);
}

static void	env_export(t_shell *shell, char *arg)
{
	char	**split;
	char	*value;

	if (!valid_var(shell, arg))
		return ;
	split = ft_split(arg, '=');
	if (ft_strchr(arg, '='))
		value = ft_strdup(ft_strchr(arg, '=') + 1);
	else
		value = NULL;
	if (get_env(split[0], shell))
		change_env(shell, split[0], value);
	else
		if (ft_strchr(arg,'='))
			add_env(shell, split[0], value, 1);
		else
			add_env(shell, split[0], value, 0);
	ft_free_array(split);
	if (value)
		free(value);
}

void	ms_export(t_shell *shell, t_exec *cmd)
{
	int		i;

	if (!cmd->argv[1])
		print_envp_sorted(shell, 1);
	else
	{
		i = 0;
		while (cmd->argv[++i])
			env_export(shell, cmd->argv[i]);
	}
}

/* static void	init_shell(t_shell *shell, char **envp)
{
	g_exit = 0;
	shell->cmd = NULL;
	shell->line = NULL;
	shell->envp_size = 0;
	envp_to_list(envp, shell);
}

//cc -o export export.c ../envp.c ../libft_obj/libft.a -g
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
