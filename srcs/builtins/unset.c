/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:12:10 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/07 17:10:16 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int args_and_fill(char **args, t_env **mini_env, t_env **new_export, int i);
int count_arg_size(char **args, int i, int *flag);
int if_invalid(char **args, int i,  int *exit_code);

int	ft_unset(char **args, t_env **mini_env, t_env **new_export)
{
	int		i;
	int		exit_code;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		return (0);
	exit_code = args_and_fill(args, mini_env, new_export, 1);
	return (exit_code);
}

int args_and_fill(char **args, t_env **mini_env, t_env **new_export, int i)
{
	int j;
	char *string;
	int flag;
	int exit_code;

	exit_code = 0;
	flag = 0;
	while (args[i] != NULL)
	{
		j = count_arg_size(args, i, &flag);
		if (flag == 0)
		{
			if (!if_invalid(args, i, &exit_code))
			{
				node_remove(mini_env, args[i], j);
				string = ft_strjoin("declare -x ", args[i]);
				node_remove(new_export, string, j + 11);
				free(string);
			}
		}
		i++;
		flag = 0;
	}
	return (exit_code);
}

int if_invalid(char **args, int i,  int *exit_code)
{
	if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
	{
		printf("minishell: %s: `%s': not a valid identifier\n",
			args[0], args[i]);
		*exit_code = 1;
		return (1);
	}
	return (0);
}

int count_arg_size(char **args, int i, int *flag)
{
	int j;
	
	j = 0;
	while (args[i][j] != '\0')
	{
		if (args[i][j] == '=')
		{
			printf("unset: %s: invalid parameter name\n", args[i]);
			*flag = 1;
			break ;
		}
		j++;
	}
	return (j);
}