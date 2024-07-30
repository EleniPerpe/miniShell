/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:51 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/30 15:32:51 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_valid(char **args, int i);
int	check_for_builtins2(char **args, t_env **mini_env, t_env **new_export);
int	check_for_builtins3(char **args, t_env **mini_env, t_env **new_export);

int check_for_builtins(char **args, t_env **mini_env, t_env **new_export)
{
	int res;
	// setup_signal_exe();
	if ((ft_strncmp(args[0], "echo", 4) == 0))
	{
		if (check_if_valid(args, 4) == 1)
			return (1);
		ft_echo(args);
		return (0);
	}
	if ((ft_strncmp(args[0], "pwd", 3) == 0))
	{
		if (check_if_valid(args, 3) == 1)
			return (1);
		ft_pwd(mini_env, args);
		return (0);
	}
	res = check_for_builtins2(args, mini_env, new_export);
	if (res != 2)
		return (res);
	return (2);
}

int	check_for_builtins2(char **args, t_env **mini_env, t_env **new_export)
{
	int res;
	
	if ((ft_strncmp(args[0], "env", 3) == 0))
	{
		if (check_if_valid(args, 3) == 1)
			return (1);
		ft_env(mini_env, args);
		return (0);
	}
	if ((ft_strncmp(args[0], "export", 6) == 0))
	{
		if (check_if_valid(args, 6) == 1)
			return (1);
		ft_export(mini_env, args, new_export);
		return (0);
	}
	res = check_for_builtins3(args, mini_env, new_export);
	if (res != 3)
		return (res);
	return (2);
}

int	check_for_builtins3(char **args, t_env **mini_env, t_env **new_export)
{
	if ((ft_strncmp(args[0], "unset", 5) == 0))
	{
		if (check_if_valid(args, 5) == 1)
			return (1);
		ft_unset(args, mini_env, new_export);
		return (0);
	}
	if ((ft_strncmp(args[0], "cd", 2) == 0))
	{
		if (check_if_valid(args, 2) == 1)
			return (1);
		ft_cd(mini_env, args, new_export);
		return (0);
	}
	if ((ft_strncmp(args[0], "exit", 4) == 0) || (ft_strncmp(args[0], "EXIT", 4) == 0))
	{
		if (check_if_valid(args, 4) == 1)
			return (1);
        ft_exit(args);
        return 0;
	}
	return (2);
}

int	check_if_valid(char **args, int i)
{
	if (args[0][i] != '\0')
	{
		printf("Command not found: %s\n", args[0]);
		return (1);
	}
	return (0);
}
