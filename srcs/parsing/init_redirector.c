/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:51:11 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 18:27:52 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_redirection_cases(char *line, int i, t_line_data *new_line_data);

int	redirection_fill(char *line, int i, t_line_data **data)
{
	t_line_data	*new_line_data;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	i = check_redirection_cases(line, i, new_line_data);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\'' || line[i] == '"')
		i = quote_token(line, i, &new_line_data, 0);
	else
		i = after_redirection_decision(line, i, &new_line_data);
	add_node_to_list(data, new_line_data);
	return (i);
}

int	check_redirection_cases(char *line, int i, t_line_data *new_line_data)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		new_line_data->type = 2;
		init_nodes_redirctor(&new_line_data, 2);
		i += 2;
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		new_line_data->type = 3;
		init_nodes_redirctor(&new_line_data, 3);
		i = i + 2;
	}
	else if (line[i] == '>' && !(line[i + 1] == '>'))
	{
		new_line_data->type = 4;
		init_nodes_redirctor(&new_line_data, 4);
		i++;
	}
	else if (line[i] == '<' && !(line[i + 1] == '<'))
	{
		new_line_data->type = 5;
		init_nodes_redirctor(&new_line_data, 5);
		i++;
	}
	return (i);
}

int	after_redirection_decision(char *line, int i, t_line_data **data)
{
	int			j;
	t_line_data	*tmp;

	tmp = *data;
	if (tmp->type == 2)
		j = heredoc_init(line, i, data);
	else
		j = after_redirection_fill(line, i, data);
	return (j);
}

int	after_redirection_fill(char *line, int i, t_line_data **data)
{
	t_line_data	*new_line_data;
	int			j;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i + j] != ' ' && line[i + j] != '\0' && line[i + j] != '\''
		&& line[i + j] != '"' && line[i + j] != '>' && line[i + j] != '<')
		j++;
	new_line_data->after_redirctor = (char *)ft_malloc(j + 1);
	new_line_data->after_redirctor = ft_memcpy(new_line_data->after_redirctor,
			&line[i], j);
	new_line_data->after_redirctor[j] = '\0';
	new_line_data->type = 7;
	new_line_data->next = NULL;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	printf("herdoc is: %s\n", new_line_data->after_redirctor );
	add_node_to_list(data, new_line_data);
	return (i + j);
}
