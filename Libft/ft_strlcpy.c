/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:41:50 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/08 20:53:34 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (size == '\0')
	{
		return (i);
	}
	while (src[j] != '\0' && j < size - 1)
	{
		dst[j] = src[j];
		j++;
	}
	if (size > 0)
	{
		dst[j] = '\0';
	}
	return (i);
}
