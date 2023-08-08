/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:28:00 by luide-so          #+#    #+#             */
/*   Updated: 2023/06/20 15:58:27 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_memmove_mod(char *buff)
{
	size_t	line_len;
	size_t	buff_len;
	size_t	i;

	line_len = ft_strclen(buff, '\n');
	if (!buff[line_len] || !buff[line_len + 1])
	{
		free (buff);
		return (NULL);
	}
	buff_len = ft_strclen(buff, '\0');
	i = -1;
	while (++i < buff_len - line_len)
		buff[i] = buff[line_len + 1 + i];
	buff[i] = '\0';
	return (buff);
}

static char	*ft_substr_line(char *buff)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	if (!buff[0])
		return (NULL);
	line_len = ft_strclen(buff, '\n');
	line = (char *)malloc(sizeof(char) * (line_len + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (++i <= line_len)
		line[i] = buff[i];
	line[i] = '\0';
	return (line);
}

static char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*c;
	size_t	len;
	int		i;
	int		j;

	len = ft_strclen(s1, '\0') + ft_strclen(s2, '\0');
	c = (char *) malloc(len * sizeof(char) + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
		c[i + j] = s2[j];
	c[i + j] = '\0';
	free (s1);
	return (c);
}

static char	*get_buffer(char *buff, int fd)
{
	int		bytes;
	char	*temp;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(buff, '\n') && bytes)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(temp);
			free(buff);
			return (NULL);
		}
		temp[bytes] = '\0';
		buff = ft_strjoin_mod(buff, temp);
	}
	free (temp);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[MAX_FILES];
	char		*line;

	if (fd < 0 || fd > MAX_FILES || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = get_buffer(buff[fd], fd);
	if (!buff[fd])
		return (NULL);
	line = ft_substr_line(buff[fd]);
	buff[fd] = ft_memmove_mod(buff[fd]);
	return (line);
}
