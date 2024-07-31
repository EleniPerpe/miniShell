/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:58:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/31 19:05:09 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_env **mini_env)
{
	t_env	*tmp;

	tmp = *mini_env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->line, "PWD=", 4) == 0)
		{
			printf("%s\n", tmp->line + 4);
			return ;
		}
		tmp = tmp->next;
	}
	change_status(mini_env, 0);
}
