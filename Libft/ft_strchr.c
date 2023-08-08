/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:21:43 by luide-so          #+#    #+#             */
/*   Updated: 2023/06/19 21:16:34 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*a;

	if (!s)
		return (0);
	a = (char *)s;
	while (*a)
	{
		if (*a == (char) c)
			return (a);
		a++;
	}
	if (*a == (char) c)
		return (a);
	return (NULL);
}
