/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:55:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/11 23:35:09 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// save some lines by using this function
// it will return a void pointer to the allocated memory
// that's why we need to cast it to the type we need each time we use it
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
// this function will add a new node to the linked list
// also to save some lines

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

void	add_node_to_commands_list(t_line_data **data,
	t_commands_list **commands_list)
{
	t_commands_list	*new_commands_list;
	t_commands_list	*tmp;

	new_commands_list = (t_commands_list *)ft_malloc(sizeof(t_commands_list));
	new_commands_list->commands_node = *data;
	new_commands_list->next = NULL;
	if (*commands_list == NULL)
		*commands_list = new_commands_list;
	else
	{
		tmp = *commands_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_commands_list;
	}
}

// I made this function to save some lines from redirection_fii()
// it will initialize the redirctor node
// it will take the type of the redirctor and initialize the redirctor node
// we can make ft_strcpy() which will allocate memory
// and copy the string to it to save more lines
void	init_nodes_redirctor(t_line_data **data, int type)
{
	t_line_data	*new_line_data;

	new_line_data = *data;
	if (type == 2)
	{
		new_line_data->redirctor = (char *)ft_malloc(3);
		new_line_data->redirctor = "<<";
	}
	else if (type == 3)
	{
		new_line_data->redirctor = (char *)ft_malloc(3);
		new_line_data->redirctor = ">>";
	}
	else if (type == 4)
	{
		new_line_data->redirctor = (char *)ft_malloc(2);
		new_line_data->redirctor = ">";
	}
	else if (type == 5)
	{
		new_line_data->redirctor = (char *)ft_malloc(2);
		new_line_data->redirctor = "<";
	}
	new_line_data->next = NULL;
	new_line_data->command = NULL;
}

int	command_fill(char *line, int i, t_line_data **data)
{
	t_line_data	*new_line_data;
	char		*tmp_command;
	int			j;

	j = 0;
	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	new_line_data->type = 0;
	while ((line[i + j] != '\0') && (line[i + j] != '<' && line[i + j] != '>')
		&& (line[i + j] != '|') && (line[i + j] != ' '))
		j++;
	if (j != 0)
	{
		tmp_command = (char *)ft_malloc(j + 1);
		tmp_command = ft_memcpy(tmp_command, &line[i], j);
		tmp_command[j] = '\0';
		new_line_data->command = ft_strdup(tmp_command);
		free(tmp_command);
		new_line_data->next = NULL;
		new_line_data->redirctor = NULL;
		new_line_data->after_redirctor = NULL;
		add_node_to_list(data, new_line_data);
	}
	return (i + j);
}
/*
this function will split the input line into a linked list of nodes
each node will contain a command or an expander or a redirctor and a file name
it will scan the input line and check if there is a redirctor or a pipe or a command
if there is a redirctor it will call the ft_split_redirctor function
if there is a pipe it will call the ft_split_pipe function .... etc
*/

char	**ft_split_line(char *input_line, t_line_data **line_data, char **env)
{
	int	i;
	char **cmd_args;

	i = 0;
	if (!input_line)
		return NULL;
	while (input_line[i] != '\0')
	{
		if (input_line[i] == '$')
		{
			input_line = expander_fill(input_line, &i, env);
		}
		i++;
	}
	i = 0;
	while (input_line[i] != '\0')
	{
		while (input_line[i] == ' ')
			i++;
		if (input_line[i] == '"' || input_line[i] == '\'')
		{
			if ((input_line[i] == '"' && input_line[i + 1] == '"')
				|| (input_line[i] == '\'' && input_line[i + 1] == '\''))
				i = i + 2;
			else
				i = quote_token(input_line, i, line_data);
		}
		else if (input_line[i] == '<' || input_line[i] == '>')
		{
			i = redirection_fill(input_line, i, line_data);
		}
		else
		{
			i = command_fill(input_line, i, line_data);
		}
		// to add later:
		// else if (input_line[i] == '|')
		// 		i = ft_split_pipe(input_line, line_data, i, '|', env);
	}
	cmd_args = command_merge(line_data);
	return (cmd_args);
	// in this step we already have the linked list of nodes
	// now we must add it to the commands list
	// to handle the pipes so each part will be in command node and will be executed in a different process
	// add_node_to_commands_list(line_data, &commands_list); // must know where to define the first commands_list .. here in this function or in start_prompt
														// t_commands_list *commands_list; // definee the commands list
}
