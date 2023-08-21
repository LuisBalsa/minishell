
#include "../../include/minishell.h"
#include <string.h>

bool	change_env(t_shell *shell, char *key, char *value);

//has to print env, ordered, but adding exported variables, even if they dont
//have a value. env should show all that have value.
static void	put_export(t_shell *shell)
{

}

static bool	valid_var(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (false);
	i = 0;
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
	}
	return (true);
}

static void	env_export(t_shell *shell, char *arg)
{
	char	**split;
	char	*value;
	char	*err;

	split = ft_split(arg, '=');
	if (!valid_var(split[0]))
	{
		ft_free_array(split);
		err = ft_strjoin(arg, ": not a valid identifier");
		print_error(shell, "export", err, 2);
		free(err);
		return ;
	}
	if (ft_strchr(arg, '='))
		value = ft_strdup(ft_strchr(arg, '=') + 1);
	else
		value = NULL;
	if (get_env(split[0], shell))
		change_env(shell, split[0], value);
	else
		add_env(shell, split[0], value);
	ft_free_array(split);
	if (value)
		free(value);
}

void	export(t_shell *shell, t_exec *cmd)
{
	int		i;

	if (!cmd->argv[1])
		put_export(shell);
	else
	{
		i = 0;
		while (cmd->argv[++i])
			env_export(shell, cmd->argv[i]);
	};
}

/*int	main(int argc, char **argv)
{
	char	*value;

	if (argc != 2)
		return (1);
	value = ft_strtrim(ft_strchr(argv[1], '='), "=");
	printf("String is %s\nValue is %s\n", argv[1], value);
	free(value);
	return (0);
}*/
