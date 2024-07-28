/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:55:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/28 07:34:32 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		&& (line[i + j] != '|') && (line[i + j] != ' ') && (line[i + j] != '"')
		&& (line[i + j] != '\''))
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

// char	**ft_split_line(char *input_line, t_line_data **line_data,
// 	t_env **mini_env, t_input **input_node)
// {
// 	int		i;
// 	char	**cmd_args;

// 	input_line = check_expander_and_rest(input_line, mini_env);
// 	i = 0;
// 	while (input_line[i] != '\0')
// 	{
// 		while (input_line[i] == ' ')
// 			i++;
// 		if (input_line[i] == '"' || input_line[i] == '\'')
// 		{
// 			if ((input_line[i] == '"' && input_line[i + 1] == '"')
// 				|| (input_line[i] == '\'' && input_line[i + 1] == '\''))
// 				i = i + 2;
// 			else
// 			{
// 				i = quote_token(input_line, i, &line_data);
// 				i--;
// 				printf("after quotes i is : %d\n",i);
// 			}
// 		}
// 		else if (input_line[i] == '<' || input_line[i] == '>')
// 		{
// 			i = redirection_fill(input_line, i, &line_data);
// 		}
// 		else
// 		{
// 			i = command_fill(input_line, i, &line_data);
// 		}
// 	}
// 	cmd_args = command_merge(&line_data);
// 	(*input_node)->data_node = line_data;
// 	return (cmd_args);
// }

char	**ft_split_line(char *input_line,/* t_line_data **line_data,*/ t_env **mini_env, t_input *input_node)
{
	int	i;
	char **cmd_args;
	t_line_data *line_data;

	line_data = NULL;
	input_line = check_expander_and_rest(input_line, mini_env);
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
				i = quote_token(input_line, i, &line_data);
		}
		else if (input_line[i] == '<' || input_line[i] == '>')
		{
			i = redirection_fill(input_line, i, &line_data);
		}
		else
		{
			i = command_fill(input_line, i, &line_data);
		}
		// to add later:
		// else if (input_line[i] == '|')
		// 		i = ft_split_pipe(input_line, line_data, i, '|', env);
	}
	cmd_args = command_merge(&line_data);
	input_node->data_node = line_data;
	return (cmd_args);
	// in this step we already have the linked list of nodes
	// now we must add it to the commands list
	// to handle the pipes so each part will be in command node and will be executed in a different process
	// add_node_to_commands_list(line_data, &commands_list); // must know where to define the first commands_list .. here in this function or in start_prompt
														// t_commands_list *commands_list; // definee the commands list
}

char	*check_expander_and_rest(char *input_line, t_env **mini_env)
{
	int	i;

	i = 0;
	if (!input_line)
		return (NULL);
	while (input_line[i] != '\0')
	{
		if (input_line[i] == ';' || input_line[i] == '\\')
		{
			printf("The program can not interpret '\\' or ';'\n");
				// kill(child_pid, SIGKILL);
				// exit(EXIT_FAILURE);
				// send a signal to kill the child process
		}
		if (input_line[i] == '$')
		{
			input_line = expander_fill(input_line, i, mini_env);
		}
		i++;
	}
	return (input_line);
}
