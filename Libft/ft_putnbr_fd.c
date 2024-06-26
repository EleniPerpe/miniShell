/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:38:33 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/11 16:04:05 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	s;

	i = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n > 9)
		ft_putnbr_fd (n / 10, fd);
	s = n % 10 + 48;
	write(fd, &s, 1);
}
