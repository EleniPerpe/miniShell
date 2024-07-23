/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:24:48 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/23 20:40:55 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_input **input_node, int **pro_pid, int **pipe_fd)
{

	t_input *free_input_node;
	t_input *tmp;
	int k = 0;

	free_input_node = *input_node;
	while (free_input_node != NULL)
	{
		tmp = free_input_node;
		free_input_node = free_input_node->next;
		free(tmp);
	}
	// if (input_node != NULL)
	// 	free(input_node);
	while (pro_pid[k] != NULL)
	{
		free(pro_pid[k]);
		k++;
	}
	if (pro_pid != NULL)
		free(pro_pid);
	k = 0;
	while (pipe_fd[k] != NULL)
	{
		free(pipe_fd[k]);
		k++;
	}
	if (pipe_fd != NULL)
		free(pipe_fd);
}
