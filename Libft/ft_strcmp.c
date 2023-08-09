/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:36:39 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/08 19:37:33 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (!s1 || !s2)
		return (-1);
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (*str1 && *str2)
	{
		if (*str1++ != *str2++)
			return (*(str1 - 1) - *(str2 - 1));
	}
	return (*str1 - *str2);
}
