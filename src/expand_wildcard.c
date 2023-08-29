/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:49:21 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/29 14:36:00 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	match_wildcard(char *pattern, char *text, int squote, int dquote)
{
	if (!*pattern && !*text)
		return (true);
	else if (!*text && *pattern == '*')
		return (match_wildcard(pattern + 1, text, squote, dquote));
	else if (*pattern == '*' && !squote && !dquote)
		return (match_wildcard(pattern + 1, text, squote, dquote)
			|| match_wildcard(pattern, text + 1, squote, dquote));
	else if (*pattern == '?' && !squote && !dquote)
		return (match_wildcard(pattern + 1, text + 1, squote, dquote));
	else if (*pattern == '\'' && !dquote)
		return (match_wildcard(pattern + 1, text, !squote, dquote));
	else if (*pattern == '"' && !squote)
		return (match_wildcard(pattern + 1, text, squote, !dquote));
	else if (*pattern == *text)
		return (match_wildcard(pattern + 1, text + 1, squote, dquote));
	else
		return (false);
}

static char	*wildcard_match_joiner(char *match, char *entry)
{
	char	*tmp;

	tmp = match;
	if (match)
	{
		match = ft_strjoin(match, " ");
		free(tmp);
		tmp = match;
		match = ft_strjoin(match, entry);
		free(tmp);
	}
	else
		match = ft_strdup(entry);
	return (match);
}

static char	*wildcard_match(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*match;

	match = NULL;
	dir = opendir(".");
	if (dir != NULL)
	{
		entry = readdir(dir);
		while (entry)
		{
			if (entry->d_name[0] != '.')
				if (match_wildcard(pattern, entry->d_name, 0, 0))
					match = wildcard_match_joiner(match, entry->d_name);
			entry = readdir(dir);
		}
		closedir(dir);
	}
	return (match);
}

static void	point_to_expand_wildcard(int *i, int j, char *tmp, t_shell *shell)
{
	char	*match;
	char	*new_line;
	char	*tmp2;

	match = wildcard_match(tmp);
	if (match)
	{
		new_line = ft_substr(shell->line, 0, *i);
		tmp2 = new_line;
		new_line = ft_strjoin(new_line, match);
		free(tmp2);
		tmp2 = new_line;
		new_line = ft_strjoin(new_line, shell->line + *i + j);
		free(tmp2);
		free(shell->line);
		shell->line = new_line;
		*i += ft_strlen(match);
	}
	else
		*i += j;
	free(match);
}

void	expand_wildcard(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (shell->line[i])
	{
		j = 0;
		while (shell->line[i] && ft_strchr(OP_AND_SP, shell->line[i]))
			i++;
		if (!shell->line[i])
			break ;
		while (shell->line[i + j] && !ft_strchr(OP_AND_SP, shell->line[i + j]))
			j++;
		tmp = ft_substr(shell->line, i, j);
		point_to_expand_wildcard(&i, j, tmp, shell);
		free(tmp);
	}
}