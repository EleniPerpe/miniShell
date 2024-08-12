/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:30:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/07 19:16:53 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit_now(int i, t_env **new_env, t_env **new_export);
void	exit_conditions(char **args, int i, t_env **mini_env,
			t_env **new_export);

int	ft_exit(char **args, t_env **mini_env, t_env **new_export,
		t_input **free_input)
{
	int	i;

	(void)free_input;
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: %s: too many arguments\n", args[0]);
		return (1);
	}
	else
		exit_conditions(args, i, mini_env, new_export);
	return (0);
}

void	exit_conditions(char **args, int i, t_env **mini_env,
			t_env **new_export)
{
	if (i == 1)
		ft_exit_now(0, mini_env, new_export);
	i = 0;
	while (args[1][i] != '\0')
	{
		if (!isdigit(args[1][i]) && !(i == 0 &&
			(args[1][i] == '-' || args[1][i] == '+')))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			ft_exit_now (255, mini_env, new_export);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	ft_exit_now(i, mini_env, new_export);
}

void	ft_exit_now(int i, t_env **mini_env, t_env **new_export)
{
	int	shlvl;

	printf("exit\n");
	shlvl = modify_shlvl(mini_env, '-');
	if (shlvl == 1)
	{
		free_env_list(mini_env);
		free_env_list(new_export);
	}
	unlink("Libft/tmp_file");
	exit(i % 256);
}
