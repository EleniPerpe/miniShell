/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:30:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 20:00:59 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include <termios.h>

void	ft_exit_now(int i);
void	exit_conditions(char **args, int i);

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: %s: too many arguments\n", args[0]);
		// free_env_list(mini_env);
		// free_env_list(new_export); // we need them for the next command
		return (1);
	}
	else
		exit_conditions(args, i);
	return (0);
}

void exit_conditions(char **args, int i)
{
	if (i == 1)
			ft_exit_now(0);
	i = 0;
	while (args[1][i] != '\0')
	{
		if (!isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			ft_exit_now (255);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	ft_exit_now(i);
}

void	ft_exit_now(int i)
{
	printf("exit\n");
	exit(i % 256);
}
