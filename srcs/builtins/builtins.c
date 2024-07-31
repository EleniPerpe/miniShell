/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:51 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/31 21:12:04 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_valid(char **args, int i);
int	check_for_builtins2(char **args, t_env **mini_env, t_env **new_export);
int	check_for_builtins3(char **args, t_env **mini_env, t_env **new_export);

int check_for_builtins(char **args, t_env **mini_env, t_env **new_export)
{
	int res;

	res = -2;
	if ((ft_strncmp(args[0], "echo", 4) == 0))
	{
		if (check_if_valid(args, 4) == 127)
			return (127);
		res = ft_echo(args);
		return (res);
	}
	if ((ft_strncmp(args[0], "pwd", 3) == 0))
	{
		if (check_if_valid(args, 3) == 1)
			return (1);
		res = ft_pwd(mini_env);
		return (res);
	}
	if (res == -2)
		res = check_for_builtins2(args, mini_env, new_export);
	return (res);
}

int	check_for_builtins2(char **args, t_env **mini_env, t_env **new_export)
{
	int res;
	
	res = -2;
	if ((ft_strncmp(args[0], "env", 3) == 0))
	{
		if (check_if_valid(args, 3) == 127)
			return (127);
		res = ft_env(mini_env, args);
		return (res);
	}
	if ((ft_strncmp(args[0], "export", 6) == 0))
	{
		if (check_if_valid(args, 6) == 127)
			return (127);
		res = ft_export(mini_env, args, new_export);
		return (res);
	}
	if (res == -2)
		res = check_for_builtins3(args, mini_env, new_export);
	return (res);
}

int	check_for_builtins3(char **args, t_env **mini_env, t_env **new_export)
{
	int res;

	res = -2;
	if ((ft_strncmp(args[0], "unset", 5) == 0))
	{
		if (check_if_valid(args, 5) == 127)
			return (127);
		res = ft_unset(args, mini_env, new_export);
		return (res);
	}
	if ((ft_strncmp(args[0], "cd", 2) == 0))
	{
		if (check_if_valid(args, 2) == 127)
			return (127);
		res = ft_cd(mini_env, args, new_export);
		return (res);
	}
	if ((ft_strncmp(args[0], "exit", 4) == 0) || (ft_strncmp(args[0], "EXIT", 4) == 0))
	{
		if (check_if_valid(args, 4) == 127)
			return (127);
        ft_exit(args, mini_env);
        return 0;
	}
	return (res);
}

int	check_if_valid(char **args, int i)
{
	if (args[0][i] != '\0')
	{
		printf("minishell: %s: command not found\n", args[0]);
		return (127);
	}
	return (0);
}
