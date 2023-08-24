#include "../../include/minishell.h"

static bool	valid_unset_var(t_shell *shell, char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i] && arg[i] != '_'))
	{
		print_error(shell, arg, ": not a valid identifier", 2);
		return (false);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_error(shell, arg, ": not a valid identifier", 2);
			return (false);
		}
	}
	return (true);
}

char	*get_key(char *key, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ms_unset(t_shell *shell, t_exec *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (valid_unset_var(shell, cmd->argv[i]))
		{
			if (get_key(cmd->argv[i], shell))
				rm_env(cmd->argv[i], shell);	
		}
	}
}
