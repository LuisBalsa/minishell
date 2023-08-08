/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:20:46 by luide-so          #+#    #+#             */
/*   Updated: 2023/06/19 18:28:02 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// const char *c is the base of the hex number, either 'x' or 'X'

#include "libft.h"

void	ft_puthex_fd(unsigned int num, const char c, int fd)
{
	if (num >= 16)
	{
		ft_puthex_fd(num / 16, c, fd);
		ft_puthex_fd(num % 16, c, fd);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd(num + '0', fd);
		else
			ft_putchar_fd(num - 33 + c, fd);
	}
}
