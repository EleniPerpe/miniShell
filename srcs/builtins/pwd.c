/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:58:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/15 17:00:15 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_pwd(t_env **mini_env)
{
	t_env *tmp = *mini_env;
    while (tmp != NULL)
    {
        printf("this is the mini_env : %s\n", tmp->line);
        tmp = tmp->next;
    }
}