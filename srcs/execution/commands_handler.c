/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:57:19 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/09 15:48:15 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**merge_free_command(t_line_data **data, int len)
{
	t_line_data	*tmp;
	int			i;
	char		**cmd_args;
	t_line_data	*tmp_delete;

	i = 0;
	tmp = *data;
	cmd_args = (char **)ft_malloc(sizeof(char *) * (len + 1));
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			cmd_args[i] = ft_strdup(tmp->command);
			i++;
			tmp_delete = tmp;
			tmp = tmp->next;
			free(tmp_delete->command);
			delete_node(data, tmp_delete);
		}
		else
			tmp = tmp->next;
	}
	cmd_args[i] = NULL;
	i = 0;
	return (cmd_args);
}

int	cmd_args_counter(t_line_data **data)
{
	int			counter;
	t_line_data	*tmp;

	counter = 0;
	tmp = *data;
	while (tmp != NULL)
	{
		if (tmp->type == 0)
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

char	**command_merge(t_line_data **data)
{
	char		**cmd_args;

	cmd_args = merge_free_command(data, cmd_args_counter(data));
	return (cmd_args);
}
