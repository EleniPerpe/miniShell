/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:28:46 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/11 20:25:11 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int		sign(long int n, int len);
char			*check_zero(char *ptr, long int i);

char	*ft_itoa(int i)
{
	char		*ptr;
	int			len;
	long int	n;

	n = (long int)i;
	len = 0;
	len = sign(n, len);
	ptr = (char *)malloc ((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	check_zero (ptr, n);
	ptr[len] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		len--;
		ptr[len] = (n % 10) + 48;
		n /= 10;
	}
	return (ptr);
}

long int	sign(long int n, int len)
{
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*check_zero(char *ptr, long int n)
{
	if (n == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	return (ptr);
}
