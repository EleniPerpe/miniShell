/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/13 07:08:19 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	child_pid = -1;

void	start_real_work(t_input **new_input_node ,char **mini_env);
void	split_pipes(char *whole_line, t_input **new_input_node);
int	create_input_node(char *whole_line, int i,t_input **new_input_node);
t_input *get_last_node(t_input **node);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);

void	start_prompt(char **env)
{
	char 		*whole_line;
	t_input		*new_input_node;
	t_env		*mini_env;

	mini_env = NULL;
	new_input_node = NULL;
	create_path(env, &mini_env);
	while (1)
	{
		whole_line = readline("minishell >");
		add_history(whole_line);
		split_pipes(whole_line, &new_input_node); // to have     --------- | --------- | ---------
//																	 |			 |			 |
//																	 |			 |			 |
//																	 v			 v			 v
//																	node1		node2		node3  `
//																	 +			  +			 +      `
//																	pipe1		pipe1		pipe2    ` linked list of t_input struct
//																				  +					/
//																				pipe1			   /
//			printout the linked list
// ##############################################################
	t_input *tmp = new_input_node;
	while (tmp != NULL)
	{
		printf("part of whole line is: %s\n", tmp->part_line);
		tmp = tmp->next;
	}
// ###############################################################
		while (new_input_node != NULL)
		{
			start_real_work(&new_input_node, env); // it was start_prompt() now it is start_real_work()
			new_input_node = new_input_node->next;
		}
	}
}

void	split_pipes(char *whole_line, t_input **new_input_node)
{
	int		i;

	i = 0;
	while (whole_line[i] != '\0')
	{
		if (whole_line[i] == '|')
			i++;
		else
			i = create_input_node(whole_line, i, new_input_node);
	}

}

int	create_input_node(char *whole_line, int i,t_input **new_input_node)
{
	t_input	*tmp;
	t_input	*tmp2;
	int		pipe_fd[2];
	int		j;

	j = 0;
	tmp = (t_input *)ft_malloc(sizeof(t_input));
	while (whole_line[i + j] != '\0' && whole_line[i + j] != '|')
		j++;
	tmp->part_line = (char *)ft_malloc(j + 1);
	tmp->part_line = ft_memcpy(tmp->part_line, &whole_line[i], j);
	tmp->part_line[j] = '\0';
	tmp->next = NULL;
	tmp->data_node = NULL;
	tmp->read_from_pipe = -99;
	tmp->write_to_pipe = -99;
	tmp->pipe_in = -99;
	tmp->pipe_out = -99;
	if (whole_line[ i + j] == '|')
	{
		pipe(pipe_fd);
		tmp->pipe_in = pipe_fd[1];
		tmp->pipe_out = pipe_fd[0];
		tmp->write_to_pipe = pipe_fd[1];
		printf("fd1 from pipe is: %d\n", tmp->pipe_in);
	}
	if (whole_line[i - 1] == '|')
	{
		tmp2 = get_last_node(new_input_node);
		if (tmp2 != NULL)
		{
			printf("fd0 from pipe is: %d\n", tmp2->pipe_out);
			tmp->read_from_pipe = tmp2->pipe_out;
		}
	}
	add_inputnode_tolist(new_input_node, tmp);
	return (i + j);
}

void	add_inputnode_tolist(t_input **data, t_input *new_line_data)
{
	t_input	*tmp;

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
t_input	*get_last_node(t_input **node)
{
	t_input	*tmp;

	tmp = *node;
	while (tmp->data_node != NULL)
		tmp = tmp->next;
//	printf("last node: %s\n",tmp->part_line);
	return (tmp);
}


void	start_real_work(t_input **new_input_node, char **mini_env)
{
	t_line_data	*line_data; // a pointer to the first element of the linked list of nodes
	t_line_data	*tmp; // a temporary pointer to iterate through the linked list
	t_input		*input_node;
	char **cmd_args;
	char *input_line;

	input_node = *new_input_node;
	while (input_node != NULL)
	{
		input_line = input_node->part_line;
		line_data = NULL;
		if (input_line && (ft_strcmp(input_line, "") != 0))
			{
				// printf("You entered : %s\n", input_line);
				cmd_args = ft_split_line(input_line, &line_data, mini_env, new_input_node);
				process_execution(&input_node, cmd_args, mini_env);

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
			// Free the path
			// free_path(mini_env);
		input_node = input_node->next;
	}
}

void	process_execution(t_input **data, char **cmd_args, char **env)
{
	child_pid = fork();
	if (child_pid < 0)
	{
		// eroor_handle
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		reset_io();
		standard_io(data);
		exec_command(cmd_args, env);
		exit(EXIT_SUCCESS);
	}
	waitpid(child_pid, 0 ,0);
		if((*data)->read_from_pipe)
			close((*data)->read_from_pipe);
		if ((*data)->write_to_pipe)
			close((*data)->write_to_pipe);
}
