/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:26:39 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/11 20:59:27 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*res;
	unsigned int	i;

	if (!s)
	{
		res = (char *)malloc (1 * sizeof(char));
		res[0] = '\0';
		return (res);
	}
	i = 0;
	len = ft_strlen(s);
	res = (char *)malloc ((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
