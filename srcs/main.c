/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/12 17:03:22 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_prompt(char **env)
{
	char		*input_line;
	t_line_data	*line_data; // a pointer to the first element of the linked list of nodes
	t_line_data	*tmp; // a temporary pointer to iterate through the linked list
	t_env *mini_env;
	char **cmd_args;	// our first list for the env (for now if it stays here)

	line_data = NULL;
	mini_env = NULL;
	create_path(env, &mini_env);
	while (1)
	{
		input_line = readline("minishell >");
		if (input_line && (ft_strcmp(input_line, "") != 0))
		{
			add_history(input_line);
			// printf("You entered : %s\n", input_line);
			cmd_args = ft_split_line(input_line, &line_data, env);
			process_execution(&line_data, cmd_args, env);
//			PRINT THE LINKED LIST
// ############################################################################
// 		tmp = line_data;
// 		while (tmp != NULL) // print the linked list to check if it's working
// 		{
// 			if (tmp->redirctor != NULL)
// 				printf("redirector is: %s\n", tmp->redirctor);
// 			if (tmp->after_redirctor != NULL)
// 				printf("File name is: %s\n", tmp->after_redirctor);
// 			// if (tmp->expander != NULL)
// 			// 	printf("expander is: %s\n", tmp->expander);
// 			if (tmp->command != NULL)
// 				printf("Command is: %s\n", tmp->command);
// 			tmp = tmp->next;
// 		}
// //			/*PRINT THE COMMAND DOUBLE ARRAY*/
// 		int k = 0;
// 		while(cmd_args[k] != NULL)
// 		{
// 			printf("command and arg [%d] = %s\n", k, cmd_args[k]);
// 			k++;
// 		}
// // ############################################################################
		// Free the linked list
			while (line_data != NULL)
			{
				tmp = line_data;
				line_data = line_data->next;
				free(tmp);
			}
			free(input_line);
		}
	}
		// Free the path
		// free_path(mini_env);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt(env);
	return (0);
}
