/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:28:35 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/17 10:13:12 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_env **mini_env, char **args)
{
	t_env *tmp;
	int i;
	
	tmp = *mini_env;
	i = 0;
	if (args == NULL || args[0] == NULL) {
        printf("env: invalid arguments\n");
        return;
    }
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		printf("env: %s: No such file or directory\n", args[1]);
		return ;
	}
	 if (mini_env == NULL || *mini_env == NULL) {
        printf("env: environment list is empty or uninitialized\n");
        return;
    }
	while (tmp != NULL)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}