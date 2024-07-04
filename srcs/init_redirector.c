/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:51:11 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/04 17:16:08 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_redirection_cases(char *line, int i, t_line_data *new_line_data);

int redirection_fill(char *line, int i, t_line_data **data, char **env)
{
	t_line_data	*new_line_data;
	// int j;

	// j = 0;
	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data)); //but ft_malloc return void pointer so we need to cast it to (t_line_data *) !very nice :)
	i = check_redirection_cases(line, i, new_line_data); // I split the cases so now it's fine											
	add_node_to_list(data, new_line_data);
	// have to add the quotes check also here
	while (line[i] == ' ')
		i++;
	if (line[i] == '\'' || line[i] == '"')
			i = quote_token(line, i, &new_line_data, env);
	else
		i = after_redirection_fill(line, i, &new_line_data);  // I don't know why the address
	return (i );
}

int check_redirection_cases(char *line, int i, t_line_data *new_line_data)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		new_line_data->type = 2;
		init_nodes_redirctor(&new_line_data, 2); // send the address of the pointer and the type of the redirctor !! very nice :)					
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

int	after_redirection_fill(char *line, int i, t_line_data **data)  //there is still a seg fault here
{
	t_line_data	*new_line_data;
	int j;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i + j] != ' ' && line[i + j] != '\0')
		j++;
	new_line_data->after_redirctor = (char *)ft_malloc(j + 1);
	new_line_data->after_redirctor= ft_memcpy(new_line_data->after_redirctor, &line[i], j);
	new_line_data->after_redirctor[j] = '\0';
	new_line_data->type = 7;
	new_line_data->next = NULL;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	add_node_to_list(data, new_line_data);
	return (i + j);
}
