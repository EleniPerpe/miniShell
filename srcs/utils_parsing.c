/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:31:40 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/11 18:22:11 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_path(t_env *mini_env)
{
	t_env	*tmp;

	while (mini_env != NULL)
	{
		tmp = mini_env;
		mini_env = mini_env->next;
		free(tmp->line);
		free(tmp);
	}
}

void	add_node_to_list(t_line_data **data, t_line_data *new_line_data)
{
	t_line_data	*tmp;

	tmp = *data;
	if (*data == NULL)
		*data = new_line_data;
	else
	{
		tmp = *data;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_line_data;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	if (ptr == NULL)
		exit (EXIT_FAILURE);
	return (ptr);
}

// I have a seg fault if I use this instead :/
// void	free_list(t_line_data *line_data)
// {
// 	t_line_data	*tmp;

// 	while (line_data != NULL)
// 	{
// 		tmp = line_data;
// 		line_data = line_data->next;
// 		free(tmp);
// 	}
// }
