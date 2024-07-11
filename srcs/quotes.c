/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:05 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/11 15:53:38 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_after_redireciton(char *line, int j, t_line_data **data);
void quotes_command(char *line, int j, t_line_data **data);
int check_quotes_cases(char *line, int *i);

int quote_token(char *line, int i, t_line_data **line_data)
{
	int j;
	int flag;
	char *tmp;

	flag = -1;
	j = 0;

	// printf("Hello from quotes function :)\n");
	while (i > 0 && (line[i] == ' '|| line[i] == '"' || line[i] == '\'')) // go back to check the previous token
		i--;
	if (i > 0)
	{	
		if (line[i] == '<' || line[i] == '>')  // if it's after_redirector, sets the flag to 7
			flag = 7;	
		else								   // else it's a command, so sets it to 0
			flag = 0;
		i++;
	}
	else
		flag = 0;
	while (line[i] == ' ' || line[i] == '"' || line[i] == '\'')  				// go again to skip the spaces
		i++;
	// printf("This is the line before the quotes : %s\n", &line[i - 1]);
	j = check_quotes_cases(line, &i);
	// if (j != 1)
	// {	
		tmp = (char *)ft_malloc(j + 1);			// create the new string in the quotes
		ft_memcpy(tmp, &line[i], j);
		tmp[j] = '\0';
		// printf("Line is :%s\n\n", tmp);
		if (flag == 7)
			quotes_after_redireciton(tmp, j, line_data);								// if it's a filename, goes to this function
		else if (flag == 0)			
		{
			// printf("Just counting times \n\n");
			quotes_command(tmp, j, line_data);
		}						// else to the functions for the commands
	// }
	// printf("to upoloipo string einai : %s\n", &line[i + j + 1]);
	free(tmp);
	return (i + j + 1);					// returns the last position after the quotes and puts it in i
}

int check_quotes_cases(char *line, int *i)
{
	int j;

	j = 0;
	(*i)--;
	if (line[*i] == '\'')
	{
		if (line[*i] == '\'' && line[*i + 1] == '\'')
			return (2);
		(*i)++;

		while (line[*i + j] != '\'' && line[*i + j] != '\0')
			j++;
	}
	else if (line[*i] == '"')
	{
		if (line[*i] == '"' && line[*i + 1] == '"')
			return (2);
		(*i)++;
		while (line[*i + j] != '"' && line[*i + j] != '\0')
			j++;
	}
	return (j);
}

void	quotes_after_redireciton(char *line, int j, t_line_data **data)
{
	t_line_data	*new_line_data;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	new_line_data->after_redirctor = (char *)ft_malloc(j + 1);
	new_line_data->after_redirctor= ft_memcpy(new_line_data->after_redirctor,
		line, j);
	new_line_data->after_redirctor[j] = '\0';
	new_line_data->type = 7;
	new_line_data->next = NULL;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	add_node_to_list(data, new_line_data);
}


void quotes_command(char *line, int j, t_line_data **data)
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
