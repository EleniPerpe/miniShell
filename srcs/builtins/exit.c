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

void	ft_exit_now(int i, t_env **mini_env);
void exit_conditions(t_env **mini_env, char **args, int i);

void	ft_exit(char **args, t_env **mini_env, t_env **new_export)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: %s: too many arguments\n", args[0]);
		free_env_list(mini_env);
		free_env_list(new_export);
		change_status(mini_env, 1);
	}
	else
		exit_conditions(mini_env, args, i);
}

void exit_conditions(t_env **mini_env, char **args, int i)
{
	if (i == 1)
			ft_exit_now(0, mini_env);
	i = 0;
	while (args[1][i] != '\0')
	{
		if (!isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			ft_exit_now(255, mini_env);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	if (i <= 255)
		ft_exit_now(i, mini_env);
	else
		ft_exit_now(255, mini_env);
}

void	ft_exit_now(int i, t_env **mini_env)
{
	printf("exit\n");
	change_status(mini_env, i);
	exit(i % 256);
}
