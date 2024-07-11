/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:31:40 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/11 15:38:05 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_path(t_env *mini_env)
{
	t_env *tmp;

	while (mini_env != NULL)
	{
		tmp = mini_env;
		mini_env = mini_env->next;
		free(tmp->line);
		free(tmp);
	}
}
