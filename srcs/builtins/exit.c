/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:30:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/30 16:03:36 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include <termios.h>

void	ft_exit_now(int i);

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minshell: %s: too many arguments\n", args[0]);
	}
	else
	{
		if (i == 1)
			ft_exit_now(0);
		i = 0;
		while (args[1][i] != '\0')
		{
			if (!isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+'))) 
			{
				printf("exit: %s: numeric argument required\n", args[1]);
				ft_exit_now(255);
			}
			i++;
		}
		i = ft_atoi(args[1]);
		if (i <= 255)
			ft_exit_now(i);
		else
			ft_exit_now(255);
	}
}

void	ft_exit_now(int i)
{
	//free everything
	// tcsetattr(0, TCSANOW, &g_data->new); what is that ?
	printf("exit\n");
	exit(i);
}
