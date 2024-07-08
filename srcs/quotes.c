/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:05 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/08 18:53:07 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_after_redireciton(char *line, int j, t_line_data **data);
void quotes_command(char *line, int j, t_line_data **data);
int check_quotes_cases(char *line, int *i);

int quote_token(char *line, int i, t_line_data **line_data)
{
	int j;
	int flag;
	char *tmp;
	int temp_j;
	
	flag = -1;
	j = 0;
	while ((line[i] == ' ' || line[i] == '"' || line[i] == '\'') && i != 0)// go back to check the previous token
		i--;
	if (line[i] == '<' || line[i] == '>')  // if it's after_redirector, sets the flag to 7
		flag = 7;
	else								   // else it's a command, so sets it to 0
		flag = 0;		
	if (i != 0)				
		i++;
	while (line[i] == ' ')  				// go again to skip the spaces
		i++;
	j = check_quotes_cases(line, &i);
	tmp = (char *)ft_malloc(j + 1);			// create the new string in the quotes
	ft_memcpy(tmp, &line[i], j);
	tmp[j] = '\0';
	// printf("Line is : %s\n", tmp);
	if (flag == 7)
	{
		temp_j = quotes_after_redireciton(tmp, j, line_data);
		if (temp_j == 0)
			;
		else
			j = temp_j; 
		
	}									// if it's a filename, goes to this function
	else if (flag == 0)									// else to the functions for the commands
		quotes_command(tmp, j, line_data);
	return (i + j + 1);									// returns the last position after the quotes and puts it in i
}

int check_quotes_cases(char *line, int *i)
{
	int j;

	j = 0;
	if (line[*i] == '\'')					// if it's single, counts till the next single
	{	
		if (line[*i] == '\'' && line[*i + 1] == '\'')
			return (0);					 
		(*i)++;				
		while (line[*i + j] != '\'' && line[*i + j] != '\0')
			j++;
	}
	else if (line[*i] == '"')				// if it's double, counts till the next double
	{
		if (line[*i] == '"' && line[*i + 1] == '"')
			return (0);		
		(*i)++;
		while (line[*i + j] != '"' && line[*i + j] != '\0')
			j++;
	}
	// printf("This is the size of the string : %d\n", j);
	return (j);
}

int	quotes_after_redireciton(char *line, int j, t_line_data **data)  //there is still a seg fault here
{
	t_line_data	*new_line_data;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	new_line_data->after_redirctor = (char *)ft_malloc(j + 1);
	new_line_data->after_redirctor= ft_memcpy(new_line_data->after_redirctor, line, j); // it does put the whole string that
	new_line_data->after_redirctor[j] = '\0';											// was in the quotes in the node
	new_line_data->type = 7;
	new_line_data->next = NULL;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	add_node_to_list(data, new_line_data);
	return (0);
}

void quotes_command(char *line, int j, t_line_data **data) 
{
	t_line_data	*new_line_data;

	// j = ft_strlen(line);
	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data)); // allocate memory for the new node
	new_line_data->type = 0; // set the type of the node to command
	new_line_data->command = (char **)ft_malloc(sizeof(char *) + 1);
	new_line_data->command[0] = (char *)ft_malloc(j + 1);
	new_line_data->command[1] = NULL;
	new_line_data->command[0]= ft_memcpy(new_line_data->command[0], line, j);
	new_line_data->command[0][j] = '\0';
	new_line_data->next = NULL;
	new_line_data->redirctor = NULL;
	new_line_data->after_redirctor = NULL;
	add_node_to_list(data, new_line_data); // add the node to the linked list
}