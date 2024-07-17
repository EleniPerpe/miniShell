/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:23:27 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/17 15:54:29 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_remove(t_env **new_export, char *line, int i);
void	env_remove(t_env **new_export, char *line, int i);

void	find_if_exists(t_env **new_export, char *line, t_env **mini_env)
{
	int i;
	
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	if (*new_export == NULL)
		return ;
	if (ft_strncmp("declare -x ", line, 11) == 0)
	{
		export_remove(new_export, line, i);
	}
	else
	{
		env_remove(mini_env, line, i);
	}
}

void export_remove(t_env **new_export, char *line, int i)
{
	t_env *curr;
	t_env *remove;
	
	if (ft_strncmp(line, (*new_export)->line, i) == 0)
	{
		remove = *new_export;
		*new_export = (*new_export)->next;
		free(remove->line);
		free(remove);
		return ;
	}
	curr = *new_export;
	while (curr->next != NULL)
	{
		if (ft_strncmp(line, curr->next->line, i) == 0)
		{
			remove = curr->next;
			curr->next = curr->next->next;
			free(remove->line);
			free(remove);
			return ;
		}
		curr = curr->next;
	}
}

void env_remove(t_env **env, char *line, int i)
{
	t_env *curr;
	t_env *remove;
	
	if (ft_strncmp(line, (*env)->line, i) == 0)
	{
		remove = *env;
		*env = (*env)->next;
		free(remove->line);
		free(remove);
		return ;
	}
	curr = *env;
	while (curr->next != NULL)
	{
		if (ft_strncmp(line, curr->next->line, i) == 0)
		{
			remove = curr->next;
			curr->next = curr->next->next;
			free(remove->line);
			free(remove);
			return ;
		}
		curr = curr->next;	
	}
}