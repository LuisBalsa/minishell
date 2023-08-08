/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:47:54 by luide-so          #+#    #+#             */
/*   Updated: 2023/06/19 18:35:35 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first_nibble(unsigned long long addr)
{
	int	i;
	int	hex;
	int	count;

	count = -1;
	i = sizeof(addr) * 2 - 1;
	hex = 0;
	while (!hex)
	{
		hex = (addr >> (i * 4)) & 0xf;
		i--;
		count++;
	}
	return (count);
}

int	print_pointer(unsigned long long addr, int *flags)
{
	int		nibble;
	int		size;
	int		i;
	char	*hex;

	if (!addr)
		return (print_str("(nil)", flags));
	size = sizeof(addr) * 2 - first_nibble(addr) + 2;
	hex = malloc(size + 1);
	if (!hex)
		return (0);
	hex[size] = '\0';
	i = size - 2;
	while (i--)
	{
		nibble = (addr >> (i * 4)) & 0xf;
		hex[size - 1 - i] = HEXBASE[nibble];
	}
	ft_memcpy(hex, "0x", 2);
	i = print_str(hex, flags);
	free (hex);
	return (i);
}
