/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:51 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/08 17:15:48 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtins2(char **args, t_env **mini_env, t_env **new_export,
		t_input **free_input);
int	execute_builtins3(char **args, t_env **mini_env, t_env **new_export,
		t_input **free_input);

int	execute_builtins(char **args, t_env **mini_env, t_env **new_export,
		t_input **free_input)
{
	int	res;

	res = -2;
	if ((args[0] != NULL) && (ft_strncmp(args[0], "echo", 4) == 0))
	{
		res = ft_echo(args);
		return (res);
	}
	if ((args[0] != NULL) && (ft_strncmp(args[0], "pwd", 3) == 0))
	{
		res = ft_pwd(mini_env);
		return (res);
	}
	if (res == -2)
		res = execute_builtins2(args, mini_env, new_export, free_input);
	return (res);
}

int	execute_builtins2(char **args, t_env **mini_env, t_env **new_export,
		t_input **free_input)
{
	int	res;

	res = -2;
	if ((args[0] != NULL) && (ft_strncmp(args[0], "env", 3) == 0))
	{
		res = ft_env(mini_env, args);
		return (res);
	}
	if ((args[0] != NULL) && (ft_strncmp(args[0], "export", 6) == 0))
	{
		res = ft_export(mini_env, args, new_export);
		return (res);
	}
	if (res == -2)
		res = execute_builtins3(args, mini_env, new_export, free_input);
	return (res);
}

int	execute_builtins3(char **args, t_env **mini_env, t_env **new_export,
		t_input **free_input)
{
	int	res;

	res = -2;
	if ((args[0] != NULL) && (ft_strncmp(args[0], "unset", 5) == 0))
	{
		res = ft_unset(args, mini_env, new_export);
		return (res);
	}
	if ((args[0] != NULL) && (ft_strncmp(args[0], "cd", 2) == 0))
	{
		res = ft_cd(mini_env, args, new_export, 0);
		return (res);
	}
	if ((args[0] != NULL) && (ft_strncmp(args[0], "exit", 4) == 0))
	{
		res = ft_exit(args, mini_env, new_export, free_input);
		return (res);
	}
	return (res);
}

int	check_if_valid(char **args, t_env **mini_env, t_env **new_export, int i)
{
	(void)new_export;
	if (args[0][i] != '\0')
	{
		printf("minishell: %s: command not found\n", args[0]);
		change_status(mini_env, 127);
		return (127);
	}
	return (0);
}
