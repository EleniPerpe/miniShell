/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:28:35 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/15 18:47:36 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_env **mini_env, char **args)
{
	t_env *tmp;
	int i;
	
	tmp = *mini_env;
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	else
	{		
	while (tmp != NULL)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
		// while (tmp != NULL)
		// {
		// 	if (ft_strncmp(tmp->line, "PWD=", 4) == 0)
		// 	{
		// 		printf("%s\n", tmp->line + 4);
		// 		// return ;

		// 	}
		// 	tmp = tmp->next;
		// }
	}
}