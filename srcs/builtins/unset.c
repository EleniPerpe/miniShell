/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:12:10 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/31 19:22:36 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void args_and_fill(char **args, t_env **mini_env, t_env **new_export, int i);

void	ft_unset(char **args, t_env **mini_env, t_env **new_export)
{
	int		i;
	
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		return ;
	args_and_fill(args, mini_env, new_export, 0);
}
void args_and_fill(char **args, t_env **mini_env, t_env **new_export, int i)
{
	int j;
	char *string;

	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '=' && args[i][j] != '\0')
			j++;
		if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
		{
			printf("minishell: %s: '%s': not a valid identifier\n",
				args[0], args[i]);
			change_status(mini_env, 1);
		}
		else
		{	
			node_remove(mini_env, args[i], j);
			string = ft_strjoin("declare -x ", args[i]);
			node_remove(new_export, string, j + 11);
			free(string);
			change_status(mini_env, 0);
		}
		i++;
	}
}
