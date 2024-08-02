/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:23:52 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/02 22:23:53 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_for_builtins2(char **args);
int	check_for_builtins3(char **args);

int check_for_builtins(char **args)
{
	int res;

	res = -2;
	if ((ft_strncmp(args[0], "echo", 4) == 0))
	{
		if (check_if_valid(args, 4) == 127)
			return (127);
		else
			return (0);
	}
	if ((ft_strncmp(args[0], "pwd", 3) == 0))
	{
		if (check_if_valid(args, 3) == 1)
			return (1);
		else
			return (0);
	}
	if (res == -2)
		res = check_for_builtins2(args);
	return (res);
}

int	check_for_builtins2(char **args)
{
	int res;

	res = -2;
	if ((ft_strncmp(args[0], "env", 3) == 0))
	{
		if (check_if_valid(args, 3) == 127)
			return (127);
		else
			return (0);
	}
	if ((ft_strncmp(args[0], "export", 6) == 0))
	{
		if (check_if_valid(args, 6) == 127)
			return (127);
		else
			return (0);
	}
	if (res == -2)
		res = check_for_builtins3(args);
	return (res);
}

int	check_for_builtins3(char **args)
{
	int res;

	res = -2;
	if ((ft_strncmp(args[0], "unset", 5) == 0))
	{
		if (check_if_valid(args, 5) == 127)
			return (127);
		else
			return (0);
	}
	if ((ft_strncmp(args[0], "cd", 2) == 0))
	{
		if (check_if_valid(args, 2) == 127)
			return (127);
		else
			return (0);
	}
	if ((ft_strncmp(args[0], "exit", 4) == 0) || (ft_strncmp(args[0], "EXIT", 4) == 0))
	{
		if (check_if_valid(args, 4) == 127)
			return (127);
		else
			return (0);
	}
	return (res);
}

