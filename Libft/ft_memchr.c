/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:37:19 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/09 12:56:00 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*us;

	i = 0;
	uc = (unsigned char)c;
	us = (unsigned char *)s;
	while (i < n)
	{
		if (us[i] == uc)
		{
			return ((void *)&us[i]);
		}
		i++;
	}
	return (NULL);
}
