/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:55:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/01 15:23:17 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	after_redirection_fill(char *line, int i, t_line_data **data);
int check_redirection_cases(char *line, int i, t_line_data *new_line_data);

// save some lines by using this function
// it will return a void pointer to the allocated memory
// that's why we need to cast it to the type we need each time we use it
void *ft_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		exit (EXIT_FAILURE);
	return (ptr);
}
// this function will add a new node to the linked list
// also to save some lines
void add_node_to_list(t_line_data **data, t_line_data *new_line_data)
{
	t_line_data *tmp;

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

// I made this function to save some lines from redirection_fii()
// it will initialize the redirctor node
// it will take the type of the redirctor and initialize the redirctor node
// we can make ft_strcpy() which will allocate memory and copy the string to it to save more lines
void init_nodes_redirctor(t_line_data **data, int type)
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
// this function is too long and couldn't split it or make it shorter :(
// tried to make it shorter by using the ft_malloc() , add_node_to_list() , init_nodes_redirctor functions
int redirection_fill(char *line, int i, t_line_data **data)
{
	t_line_data	*new_line_data;
	int j;

	j = 0;
	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data)); //but ft_malloc return void pointer so we need to cast it to (t_line_data *) !very nice :)
	i = check_redirection_cases(line, i, new_line_data); // I split the cases so now it's fine											
	add_node_to_list(data, new_line_data);
	i = after_redirection_fill(line, i, &new_line_data);
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

// ############################################################################################################
// this is the old version of the redirection_fill function

// int redirection_fill(char *line, int i, t_line_data **data)
// {
// 	t_line_data	*new_line_data;
// 	t_line_data *tmp;

// 	tmp = NULL;
// 	new_line_data = malloc(sizeof(t_line_data));
// 	if (new_line_data == NULL)
// 		return (-1);
// 	if (line[i] == '<' && line[i + 1] == '<')
// 	{
// 		new_line_data->type = 2;
// 		new_line_data->redirctor = ft_strdup("<<");
// 		if (new_line_data->redirctor == NULL)
// 			exit (EXIT_FAILURE); // it was return (-1); also need to handle leaks error_handle_free()
// 		i += 2; // it was i = 1 + 2;
// 	}
// 	else if (line[i] == '>' && line[i + 1] == '>')
// 	{
// 		new_line_data->type = 3;
// 		new_line_data->redirctor = malloc(3);
// 		if (new_line_data->redirctor == NULL)
// 			exit (EXIT_FAILURE); //leaks error_handle_free()
// 		new_line_data->redirctor = ">>";
// 		i = i + 2;
// 	}
// 	else if (line[i] == '>' && !(line[i + 1] == '>'))
// 	{
// 		new_line_data->type = 4;
// 		new_line_data->redirctor = malloc(2);
// 		if (new_line_data->redirctor == NULL)
// 			exit (EXIT_FAILURE); //leaks error_handle_free()
// 		new_line_data->redirctor = ">";
// 		i++;
// 	}
// 	else if (line[i] == '<' && !(line[i + 1] == '<'))
// 	{
// 		new_line_data->type = 5;
// 		new_line_data->redirctor = malloc(2);
// 		if (new_line_data->redirctor == NULL)
// 			exit (EXIT_FAILURE);
// 		new_line_data->redirctor = "<";
// 		i++;
// 	}
// 	new_line_data->next = NULL;
// 	printf("check 3 done, we got it\n"); // check
// 	if (*data == NULL)
// 		*data = new_line_data;
// 	else
// 	{
// 		tmp = *data;
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new_line_data;
// 	}
// 		printf("check 999 done, we got it\n"); // check
// 			printf("re is: %s\n",new_line_data->redirctor); // check

// 	i = after_redirection_fill(line, i - 1, data);
// 	return (i); // or return (i - 1);
// }
// ############################################################################################################

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

int command_fill(char *line, int i, t_line_data **data)
{
	t_line_data	*new_line_data;
	char *tmp_commands; // to save the command and the flags in one string tp split it later
	int j;

	j = 0;
	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data)); // allocate memory for the new node
	new_line_data->type = 0; // set the type of the node to command
	// to get the length of the command and the flags to allocate memory for it
	// in the while I removed != ' '  because there might be a space between the command and the flags
	while ((line[i + j] != '\0') && (line[i + j] != '<' && line[i + j] != '>') && (line[i + j] != '|'))
		j++;
	tmp_commands = (char *)ft_malloc(j + 1);
	tmp_commands = ft_memcpy(tmp_commands, &line[i], j);
	tmp_commands[j] = '\0';
	new_line_data->command = ft_split((char const *)tmp_commands, ' '); // split the command and the flags and save it in the node
	new_line_data->next = NULL;
	new_line_data->redirctor = NULL;
	new_line_data->after_redirctor = NULL;
	add_node_to_list(data, new_line_data); // add the node to the linked list
	return (i + j);
}
/*
this function will split the input line into a linked list of nodes
each node will contain a command or an expander or a redirctor and a file name
it will scan the input line and check if there is a redirctor or a pipe or a command
if there is a redirctor it will call the ft_split_redirctor function
if there is a pipe it will call the ft_split_pipe function .... etc
*/

void ft_split_line(char *input_line, t_line_data **line_data, char **env)
{
	int i;

	char *path = env[0];
	printf("PATH : %s\n", path);
	i = 0;
	if(!input_line)
		return ;
	while(input_line[i] != '\0')
	{
		while(input_line[i] == ' ')
			i++;
		if(input_line[i] == '<' || input_line[i] == '>')
		{
			i = redirection_fill(input_line, i, line_data);
		}
		else if (input_line[i] != ' ' && input_line[i] != '\0' && input_line[i] != '|')
		{
			i = command_fill(input_line, i, line_data);
		}
		// to add later:
		// else if (input_line[i] == '|')
		// 		i = ft_split_pipe(input_line, line_data, i, '|', env);
	}
}
