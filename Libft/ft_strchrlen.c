/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:48:49 by luide-so          #+#    #+#             */
/*   Updated: 2023/08/10 02:28:19 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strchrlen(const char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str && str[i] && !ft_strchr(set, str[i]))
		i++;
	return (i);
}
