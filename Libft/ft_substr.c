/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:00:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/14 15:17:29 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
	{
		ptr = (char *)malloc(1 * sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr[i] = '\0', ptr);
	}
	if (slen < (start + len))
		len = slen - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	return (ptr[i] = '\0', ptr);
}
