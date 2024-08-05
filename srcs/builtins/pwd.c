/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:58:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 18:18:59 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_env **mini_env)
{
	t_env	*tmp;

	tmp = *mini_env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->line, "PWD=", 4) == 0)
		{
			printf("%s\n", tmp->line + 4);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}
