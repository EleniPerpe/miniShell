/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:12:10 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/23 12:53:05 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_unset(char **args, t_env **mini_env, t_env **new_export)
{
	int i;
	int j;
	char *string;
	
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '=' && args[i][j] != '\0')
			j++;
		node_remove(mini_env, args[i], j);
		string = ft_strjoin("declare -x ", args[i]);
		node_remove(new_export, string, j + 11);
		free(string);	
		i++;
	}
}