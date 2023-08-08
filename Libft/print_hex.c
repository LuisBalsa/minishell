/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:38:43 by luide-so          #+#    #+#             */
/*   Updated: 2023/07/07 08:37:16 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_nbr_right(unsigned int nbr, int *flags, const char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < flags[7])
		i += write(1, " ", 1);
	if (flags[2])
	{
		flags[2] = write(1, "0", 1);
		flags[2] += write(1, &c, 1);
	}
	while (j < flags[6])
		j += write(1, "0", 1);
	if (flags[5] < 2)
		ft_puthex_fd(nbr, c, 1);
	return (i + j + flags[2]);
}

static int	print_nbr_left(unsigned int nbr, int *flags, const char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (flags[2])
	{
		flags[2] = write(1, "0", 1);
		flags[2] += write(1, &c, 1);
	}
	while (j < flags[6])
		j += write(1, "0", 1);
	if (flags[5] < 2)
		ft_puthex_fd(nbr, c, 1);
	while (i < flags[7])
		i += write(1, " ", 1);
	return (i + j + flags[2]);
}

int	print_hex(unsigned int nbr, int *flags, const char c)
{
	int	len;

	len = ft_intlen(nbr, 16);
	if (!nbr)
		flags[2] = 0;
	if (flags[5] && !flags[6] && !nbr)
		flags[5] += len--;
	if (flags[4] && !flags[5])
	{
		flags[6] = flags[7];
		flags[7] = 0;
	}
	if (flags[6] > len)
		flags[7] -= flags[6];
	else
		flags[7] -= len ;
	if (flags[5])
		flags[6] -= len;
	else
		flags[6] -= len ;
	if (flags[3])
		return (len + print_nbr_left(nbr, flags, c));
	return (len + print_nbr_right(nbr, flags, c));
}
