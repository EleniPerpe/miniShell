/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:00:29 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/02 18:15:37 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_path_to_list(t_env **mini_env, t_env *new_env);

void create_path(char **env, t_env **mini_env)
{
	t_env *new_env;
	t_env *tmp;
	int i;
	int j;

	i = 0;
	// while (env[i] != NULL)
	// {
	// 	printf("Env : %s\n", env[i]);
	// 	i++;
	// }
	while (env[i] != NULL)
	{
		new_env = (t_env *)ft_malloc(sizeof(t_env));
		j = ft_strlen(env[i]);
		new_env->line = (char *)ft_malloc(j + 1);
		ft_strlcpy(new_env->line, env[i], j);
		new_env->line[j] = '\0';
		new_env->next = NULL;
		add_path_to_list(mini_env, new_env);
		i++;
	}

	tmp = *mini_env; // prints the path
	while (tmp != NULL)
	{
		printf("Next line : %s\n", tmp->line);
		tmp = tmp->next;
	}
	
	// for later
	
	// while (new_env != NULL)
	// {
	// 	tmp = new_env;
	// 	new_env = new_env->next;
	// 	free(tmp);
	// }
}

void add_path_to_list(t_env **mini_env, t_env *new_env)
{
	t_env *tmp;

	if (*mini_env == NULL)
		*mini_env = new_env;
	else
	{
		tmp = *mini_env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}
