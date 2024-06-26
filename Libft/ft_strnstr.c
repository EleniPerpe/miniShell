/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:22:59 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/10 14:43:55 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	int			j;

	if (len < 0 || (!*haystack && *needle))
		return (0);
	i = 0;
	if (*needle == '\0' || needle == haystack)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
