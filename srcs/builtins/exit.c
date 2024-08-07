/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:30:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/07 13:24:21 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include <termios.h>

void	ft_exit_now(int i, t_env **mini_env, t_env **new_export);
void exit_conditions(t_env **mini_env, t_env **new_export, char **args, int i);

void	ft_exit(char **args, t_env **mini_env, t_env **new_export)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: %s: too many arguments\n", args[0]);
		change_status(mini_env, 1);
	}
	else
		exit_conditions(mini_env, new_export, args, i);
}

void exit_conditions(t_env **mini_env, t_env **new_export, char **args, int i)
{
	if (i == 1)
			ft_exit_now(0, mini_env, new_export);
	i = 0;
	while (args[1][i] != '\0')
	{
		if (!isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			ft_exit_now(255, mini_env, new_export);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	if (i <= 255)
		ft_exit_now(i, mini_env, new_export);
	else
		ft_exit_now(255, mini_env, new_export);
}

void	ft_exit_now(int i, t_env **mini_env, t_env **new_export)
{
	printf("exit\n");
	change_status(mini_env, i);
	free_env_list(mini_env);
	free_env_list(new_export);
	exit(i % 256);
}
