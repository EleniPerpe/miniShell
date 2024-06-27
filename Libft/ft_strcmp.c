/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:57:23 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/27 16:10:58 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
    while (s1[i] != '\0' && (s1[i] == s2[i]))
		i++;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
