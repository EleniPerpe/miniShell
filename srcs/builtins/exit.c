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

void	ft_exit_now(int i, t_input **free_input);
void	exit_conditions(char **args, int i, t_input **free_input);

int	ft_exit(char **args, t_input **free_input)
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
		exit_conditions(args, i, free_input);
	return (0);
}

void exit_conditions(char **args, int i, t_input **free_input)
{
	if (i == 1)
			ft_exit_now(0, free_input);
	i = 0;
	while (args[1][i] != '\0')
	{
		if (!isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			ft_exit_now (255, free_input);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	ft_exit_now(i, free_input);
}

void	ft_exit_now(int i, t_input **free_input)
{
	t_input *free_node;

	free_node = *free_input;
	printf("exit\n");
	free_all(&free_node, NULL, NULL);
	exit(i % 256);
}
