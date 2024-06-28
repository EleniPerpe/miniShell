/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/29 01:20:21 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_prompt(void)
{
	char		*input_line;
	t_line_data	*line_data; // a pointer to the first element of the linked list of nodes

	line_data = NULL;
	while (1)
	{
		input_line = readline("minishell >");
		if (input_line && (ft_strcmp(input_line, "") != 0))
		{
			add_history(input_line);
			printf("You entered : %s\n", input_line);
			ft_split_line(input_line, &line_data);
		while(line_data) // print the linked list to check if it's working
		{
			printf("%s\n", line_data->redirctor);
			line_data = line_data->next;
		}
		if (line_data) // free the linked list
			free(line_data);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	(void)env;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt();

	return (0);
}
