/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:51 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/16 18:05:18 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_for_builtins(char **args, t_env **mini_env, char **env)
{
	//need to fix the command not found if it is echos for example instead of doing nothing
	if ((ft_strcmp(args[0], "echo") == 0) || (ft_strcmp(args[0], "ECHO") == 0))
	{
		if (args[0][4] != '\0')
        {
            printf("Command not found: %s\n", args[0]);
            return 1;
        }
        ft_echo(args);
        return 0;
	}
	if ((ft_strcmp(args[0], "pwd") == 0) || (ft_strcmp(args[0], "PWD") == 0))
	{
		if (args[0][3] != '\0')
        {
            printf("Command not found: %s\n", args[0]);
            return 1;
        }
        ft_pwd(mini_env, args);
        return 0;
	}
	if ((ft_strcmp(args[0], "env") == 0) || (ft_strcmp(args[0], "ENV") == 0))
	{
		if (args[0][3] != '\0')
        {
            printf("Command not found: %s\n", args[0]);
            return 1;
        }
        ft_env(mini_env, args);
        return 0;
	}
	if ((ft_strcmp(args[0], "export") == 0) || (ft_strcmp(args[0], "EXPORT") == 0))
	{
		if (args[0][6] != '\0')
        {
            printf("Command not found: %s\n", args[0]);
            return 1;
        }
        ft_export(mini_env, args, env);
        return 0;
	}
	// if ((ft_strcmp(args[0], "unset") == 0) || (ft_strcmp(args[0], "UNSET") == 0))
	// {
	// 	if (args[0][5] != '\0')
    //     {
    //         printf("Command not found: %s\n", args[0]);
    //         return 1;
    //     }
    //     ft_unset(mini_env, args);
    //     return 0;
	// }
	// if ((ft_strcmp(args[0], "exit") == 0) || (ft_strcmp(args[0], "EXIT") == 0))
	// {
	// 	if (args[0][4] != '\0')
    //     {
    //         printf("Command not found: %s\n", args[0]);
    //         return 1;
    //     }
    //     ft_exit(mini_env, args);
    //     return 0;
	// }
	return (1);
}