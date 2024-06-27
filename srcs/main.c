/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/27 14:43:06 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell_data(t_shell_data *data);

int	main(int argc, char **argv, char **env)
{
	char			*input_line;
	t_shell_data	*shell_data;

	(void)argv;
	(void)env;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	shell_data = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell_data)
	{
		perror("Failed to allocate memory");
		return (1);
	}
	init_shell_data(shell_data);
	input_line = readline("minishell >");
	if (input_line)
	{
		add_history(input_line);
		printf("You entered : %s\n", input_line);
		input_line = shell_data->prompt_line;
		free(input_line);
	}
	return (0);
}

void	init_shell_data(t_shell_data *data)
{
	data->prompt_line = NULL;
	data->prompt_name = NULL;
	data->shell_env = NULL;
}
