/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:30:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/31 20:45:58 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include <termios.h>

void	ft_exit_now(int i, t_env **mini_env);

void	ft_exit(char **args, t_env **mini_env)
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

}

void	ft_exit_now(int i, t_env **mini_env)
{
	//free everything
	// tcsetattr(0, TCSANOW, &g_data->new); what is that ?
	printf("exit\n");
	change_status(mini_env, i);
	exit(i % 256);
}
