/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 01:20:46 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/07 18:45:33 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_status(t_env **mini_env, int status)
{
	t_env	*current_env;
	char	*status_ch;
	char	*temp;

	temp = ft_itoa(status);
	status_ch = ft_strjoin("?=", temp);
	current_env = *mini_env;
	while (current_env != NULL)
	{
		if ((current_env->line) && (current_env->line[0] == '?'
				&& current_env->line[1] == '='))
		{
			free(current_env->line);
			current_env->line = ft_strdup(status_ch);
		}
		current_env = current_env->next;
	}
	free(status_ch);
	free(temp);
}

void	add_status(t_env **mini_env)
{
	t_env	*new_env;

	new_env = (t_env *)ft_malloc(sizeof(t_env));
	new_env->line = ft_strdup("?=0");
	if (!new_env->line)
	{
		free(new_env);
		exit(EXIT_FAILURE);
	}
	new_env->next = NULL;
	add_path_to_list(mini_env, new_env);
}
