/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/22 17:29:21 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void ft_cd(t_env **mini_env, char **args)
// {
// 	int i;
// 	// t_env *temp;
// 	// char *new_pwd;
// 	// char *rest;
// 	// int len;

// 	(void)*mini_env;
// 	i = 0;
// 	while (args[i] != NULL)
// 		i++;
// 	printf("Hi\n");
// 	// if (i == 1)
// 	// {
// 	// 	while (temp->next != NULL)
// 	// 	{
// 	// 		if (ft_strncmp(temp->line, "PWD", 3) == 0)
// 	// 		{
// 	// 			rest = ft_strrchr(temp->line, '/');
// 	// 			len = ft_strlen(rest);
// 	// 			new_pwd = ft_substr(temp->line, 0, (ft_strlen(temp->line) - len));
// 	// 			// export_remove(mini_env, temp->line, 3);
// 	// 			printf("New pwd is: %s\n", new_pwd);
// 	// 			temp->line = new_pwd;
// 	// 			temp->next = NULL;
// 	// 			add_path_to_list(mini_env, temp);
// 	// 			break ;
// 	// 		}
// 	// 		temp = temp->next;
// 	// 	}
// 	// }
// }