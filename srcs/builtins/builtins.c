/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:51 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/15 16:59:48 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void check_for_builtins(char **args, t_env **mini_env)
{
	if ((ft_strcmp(args[0], "echo") == 0))
	{
		ft_echo(args);
	}
	if ((ft_strcmp(args[0], "pwd") == 0))
	{
		ft_pwd(mini_env);
	}
}