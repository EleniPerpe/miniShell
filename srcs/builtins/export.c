/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:57:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/16 16:08:17 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_export(t_env **mini_env, char **args)
{
	int i;
	t_env *new_env;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL && (ft_isalpha(args[i][0]) || args[i][0] == '_'))
		{	
			new_env = (t_env *)ft_malloc(sizeof(t_env));
			new_env->line = ft_strdup(args[1]);
			if (!new_env->line)
			{
				free(new_env);
				exit(EXIT_FAILURE);
			}
			new_env->next = NULL;
			add_path_to_list(mini_env, new_env);
		}	
		else
		{
			
			if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
				printf("minishell: %s: '%s': not a valid identifier\n", args[0], args[i]);
		}
		i++;
	}
}