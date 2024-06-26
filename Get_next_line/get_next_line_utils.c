/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:29:37 by eperperi          #+#    #+#             */
/*   Updated: 2024/04/07 20:42:30 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	n;

	n = ft_strlen(s1) + 1;
	ptr = (char *) malloc(n * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, n);
	return (ptr);
}

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

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
