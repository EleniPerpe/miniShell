/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:51 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/15 18:55:45 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_for_builtins(char **args, t_env **mini_env)
{
	//need to fix the command not found if it is echos for example instead of doing nothing
	if (((ft_strcmp(args[0], "echo") == 0) || (ft_strcmp(args[0], "ECHO") == 0)))
	{
		if (args[0][4] != '\0')
			;
		else
		{	
			ft_echo(args);
			return (0);
		}
	}
	if (((ft_strcmp(args[0], "pwd") == 0) || (ft_strcmp(args[0], "PWD") == 0)) && args[0][3] == '\0')
	{
		ft_pwd(mini_env, args);
		return (0);
	}
	// I have seg fault and I don't know why
	if (((ft_strcmp(args[0], "env") == 0) || (ft_strcmp(args[0], "ENV") == 0)) && args[0][3] == '\0')
	{
		ft_env(mini_env, args);
		return (0);
	}
	return (1);
}