/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:49:21 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/13 11:59:23 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

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
	char	*tmp_entry;

	tmp = ft_strjoin("\"", entry);
	tmp_entry = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = match;
	if (match)
	{
		match = ft_strjoin(match, " ");
		free(tmp);
		tmp = match;
		match = ft_strjoin(match, tmp_entry);
		free(tmp);
	}
	else
		match = ft_strdup(tmp_entry);
	free(tmp_entry);
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

static void	point_to_expand_wildcard(int *i, int j, char *tmp, char **line)
{
	char	*match;
	char	*new_line;
	char	*tmp2;

	match = NULL;
	if (ft_strchr(tmp, '*') || ft_strchr(tmp, '?'))
		match = wildcard_match(tmp);
	if (match)
	{
		new_line = ft_substr(*line, 0, *i);
		tmp2 = new_line;
		new_line = ft_strjoin(new_line, match);
		free(tmp2);
		tmp2 = new_line;
		new_line = ft_strjoin(new_line, *line + *i + j);
		free(tmp2);
		free(*line);
		*line = new_line;
		*i += ft_strlen(match);
	}
	else
		*i += j;
	free(match);
	free(tmp);
}

void	expand_wildcard(char **line)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (line[0][i])
	{
		j = 0;
		quote = '\0';
		while (line[0][i] && ft_strchr(SPACES, line[0][i]))
			i++;
		while (line[0][i + j] && (!ft_strchr(SPACES, line[0][i + j]) || quote))
		{
			if (!quote && (line[0][i + j] == '\'' || line[0][i + j] == '"'))
				quote = line[0][i + j];
			else if (quote == line[0][i + j])
				quote = '\0';
			j++;
		}
		point_to_expand_wildcard(&i, j, ft_substr(*line, i, j), line);
	}
}
