/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:51:32 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/22 11:36:37 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ptr;
	size_t	i;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < s1len)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		ptr[s1len + i] = s2[i];
		i++;
	}
	ptr[s1len + s2len] = '\0';
	return (ptr);
}
