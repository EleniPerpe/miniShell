/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/11 18:21:07 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_prompt(char **env)
{
	char		*input_line;
	t_line_data	*line_data;
	t_line_data	*tmp;
	t_env		*mini_env;

	line_data = NULL;
	mini_env = NULL;
	create_path(env, &mini_env);
	while (1)
	{
		input_line = readline("minishell >");
		if (input_line && (ft_strcmp(input_line, "") != 0))
		{
			add_history(input_line);
			ft_split_line(input_line, &line_data, env);
			// process_execution(&line_data, env);
			tmp = line_data;
			while (tmp != NULL)
			{
				if (tmp->redirctor != NULL)
					printf("redirector is: %s\n", tmp->redirctor);
				if (tmp->after_redirctor != NULL)
					printf("File name is: %s\n", tmp->after_redirctor);
				if (tmp->command != NULL)
					printf("Command is: %s\n", tmp->command);
				tmp = tmp->next;
			}
			// free_list(line_data);
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
