/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:36:31 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 18:38:00 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quotes_after_redireciton(char *line, int j, t_line_data **data)
{
	t_line_data	*new_line_data;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	new_line_data->after_redirctor = (char *)ft_malloc(j + 1);
	new_line_data->after_redirctor = ft_memcpy(new_line_data->after_redirctor,
			line, j);
	new_line_data->after_redirctor[j] = '\0';
	new_line_data->type = 7;
	new_line_data->next = NULL;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	add_node_to_list(data, new_line_data);
}

void	quotes_command(char *line, int j, t_line_data **data)
{
	t_line_data	*new_line_data;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	new_line_data->command = (char *)ft_malloc(j + 1);
	new_line_data->command = ft_memcpy(new_line_data->command, line, j);
	new_line_data->command[j] = '\0';
	new_line_data->type = 0;
	new_line_data->next = NULL;
	new_line_data->redirctor = NULL;
	new_line_data->after_redirctor = NULL;
	add_node_to_list(data, new_line_data);
}

int	qoute_fill(char *line, int i, t_line_data **data)
{
	if ((line[i] == '"' && line[i + 1] == '"')
		|| (line[i] == '\'' && line[i + 1] == '\''))
		i = i + 2;
	else
		i = quote_token(line, i, data, 0);
	return (i);
}
