/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:56:41 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/17 11:01:39 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_echo(char **args)
{
	int i;
	
	i = 1;
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		i++;
		while (args[i] != NULL)
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		while (args[i] != NULL)
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		if (args[1] != NULL)
			printf("\n");
	}
}