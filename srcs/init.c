/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:55:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/06/29 01:34:47 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*split_after_redirctor(char *input_line)
{
	char	*after_redirctor;
	int		i;

	i = 0;
	printf("check 2 done, we got it\n"); // check
	// strlen of the file name:
	while(input_line[i] && input_line[i] != ' ' &&
			input_line[i] != '|' && input_line[i] != '<' && input_line[i] != '>')
		i++;
		
	after_redirctor = malloc(sizeof(char) * (i + 1));
	if(!after_redirctor)
		return (NULL);
	i = 0;
	while(input_line[i] && input_line[i] != ' ' &&
			input_line[i] != '|' && input_line[i] != '<' && input_line[i] != '>')
	{
		after_redirctor[i] = input_line[i];
		i++;
	}
	after_redirctor[i] = '\0';
	printf("check 3 done, we got it\n"); // check
	return (after_redirctor);
}

char	*ft_split_redirctor(char *input_line, t_line_data **line_data)
{
	t_line_data	*new_line_data;
	t_line_data *tmp;

	new_line_data = malloc(sizeof(t_line_data));
	if(!new_line_data)
		return NULL;
	new_line_data = malloc(sizeof(t_line_data));
	if(!new_line_data)
		return NULL;
	new_line_data->command = NULL;
	// new_line_data->expander = NULL; // to be added later
	if(*input_line == '<')
	{
		if(*(input_line + 1) == '<') //if the next char is also '<' that means we have "<<"
		{
			new_line_data->type = 2;
			new_line_data->redirctor = "<<";
			input_line++;
		}
		else // if the next char is not '<' that means we have  only "<"
		{
			new_line_data->type = 5;
			new_line_data->redirctor = "<";
		}
		input_line++;
	}
	else if(*input_line == '>')
	{
		if(*(input_line + 1) == '>')
		{
			new_line_data->type = 3;
			new_line_data->redirctor = ">>";
			input_line++;
		}
		else
		{
			new_line_data->type = 4;
			new_line_data->redirctor = ">";
		}
		input_line++;
	}
	new_line_data->after_redirctor = split_after_redirctor(input_line);
	printf("%d\n", new_line_data->type); // check
	printf("%s\n", new_line_data->redirctor); // check
	printf("%s\n", new_line_data->after_redirctor); // check
	// Here below we have the segmentaion fault:
	// because I can't see the check 4 in the output
	if (line_data == NULL) // if the linked list is empty which means this is the first node
		*line_data = new_line_data; // the first node is the new node we just created
	else
	{
		tmp = *line_data;
		while(tmp->next) // if the linked list is not empty we need to go to the last node
			tmp = tmp->next;
		tmp->next = new_line_data; // add the new node to the end of the linked list
	}
	printf("check 4 done, we got it\n"); // check // can't see it in the output
	return (input_line + ft_strlen(new_line_data->after_redirctor)); // return the address of the first char after the redirctor and the file
}


/*
this function will split the input line into a linked list of nodes
each node will contain a command or an expander or a redirctor and a file name
it will scan the input line and check if there is a redirctor or a pipe or a command
if there is a redirctor it will call the ft_split_redirctor function
if there is a pipe it will call the ft_split_pipe function .... etc


*/
void ft_split_line(char *input_line, t_line_data **line_data)
{
	line_data = NULL;
	if(!input_line)
		return ;
	while(*input_line)
	{
		while(*input_line == ' ')
			input_line++;
		if(*input_line == '<')
		{
			printf("check 1 done, we got it\n"); // check
			input_line = ft_split_redirctor(input_line, line_data);
		}
		else if (*input_line == '>')
				input_line = ft_split_redirctor(input_line, line_data);
		// to add later:
		// else if (*input_line == '|')
		// 		input_line = ft_split_pipe(input_line, line_data, "|");
		// else
		// 		input_line = ft_split_command(input_line, line_data);
	}
}
