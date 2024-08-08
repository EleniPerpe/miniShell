/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:24:48 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/08 19:31:19 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_all(t_input **input_node, int **pro_pid, int **pipe_fd)
{

	t_input *free_input_node;
	t_input *tmp;
	t_line_data *free_node;
	t_line_data *tmp2;

	(void)pro_pid;
	(void)pipe_fd;
	free_input_node = *input_node;
	while (free_input_node != NULL)
	{
		free_node = free_input_node->data_node;
		while (free_node != NULL)
		{
			tmp2 = free_node;
			free_node = free_node->next;
			free(tmp2);
		}
		if (free_input_node->cmd_args != NULL)
		{
			free_split(free_input_node->cmd_args);
		}
		tmp = free_input_node;
		free_input_node = free_input_node->next;
		free(tmp);
	}
	// if (input_node != NULL)
	// 	free(input_node);
	// while (pro_pid[k] != NULL)
	// {
	// 	free(pro_pid[k]);
	// 	k++;
	// }
	// if (pro_pid != NULL)
	// 	free(pro_pid);
	// k = 0;
	// if(pipe_fd)
	// {
	// 	while (pipe_fd[k] != NULL)
	// 	{
	// 		free(pipe_fd[k]);
	// 		k++;
	// 	}
	// 	if (pipe_fd != NULL)
	// 		free(pipe_fd);
	// }
}

void free_env_list(t_env **env)
{
    t_env *current = *env;
    t_env *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
    *env = NULL;
}
void free_split(char **args)
{
	int i;

	if (args == NULL || *args == NULL)
		return;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	// args = NULL;
}

void free_nodes(t_input **input_node)
{
	t_input *free_input_node;
	t_input *tmp;
	t_line_data *free_node;
	t_line_data *tmp2;

	if (input_node != NULL)
	{
		free_input_node = *input_node;
		while (free_input_node != NULL)
		{
			free_node = free_input_node->data_node;
			while (free_node != NULL)
			{
				tmp2 = free_node;
				free_node = free_node->next;
				free(tmp2);
			}
			tmp = free_input_node;
			free_input_node = free_input_node->next;
			free(tmp);
		}
	}
}
