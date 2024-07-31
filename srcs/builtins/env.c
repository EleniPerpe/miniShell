/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:28:35 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/31 19:09:55 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_env(t_env **mini_env);

void	ft_env(t_env **mini_env, char **args)
{
	int		i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		printf("env: %s: No such file or directory\n", args[1]);
		change_status(mini_env, 127);
		exit_code = 1;
		return ;
	}
	if (mini_env == NULL || *mini_env == NULL)
	{
		printf("env: environment list is empty or uninitialized\n");
		change_status(mini_env, 1);
		exit_code = 1;
		return ;
	}
	print_env(mini_env);
	change_status(mini_env, 0);
}

void print_env(t_env **mini_env)
{
	t_env	*tmp;
	
	tmp = *mini_env;
	while (tmp != NULL)
	{
		if (tmp->line[0] == '?' && tmp->line[1] == '=') // Do not print the status :D
			tmp = tmp->next;
		else
		{
			printf("%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
}
