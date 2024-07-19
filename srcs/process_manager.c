/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/19 08:04:03 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_pipes(char *whole_line, t_input **new_input_node);
int	create_input_node(char *whole_line, int i,t_input **new_input_node);
t_input *get_last_node(t_input **node);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);
void	close_fds(t_input **data);
void	wait_for_children(t_input **data);
void	fork_and_exec(t_input **data, char **env);

void	start_prompt(char **env)
{
	char 		*whole_line;
	t_input		*new_input_node;
	t_env		*mini_env;
	t_env		*new_export;

	mini_env = NULL;
	new_input_node = NULL;
	create_path(env, &mini_env);
	new_export = NULL;
	create_export_path(&mini_env, &new_export);
	while (1)
	{
		reset_io();
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

		init_linked_list(&new_input_node, &mini_env, env, &new_export);
		fork_and_exec(&new_input_node, env);
		wait_for_children(&new_input_node);
		close_fds(&new_input_node);

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
	}
	if (i > 0 && whole_line[i - 1] == '|')
	{
		tmp2 = get_last_node(new_input_node);
		if (tmp2 != NULL)
			tmp->read_from_pipe = tmp2->pipe_out;
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
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}


void	init_linked_list(t_input **new_input_node, t_env **mini_env, char **env, t_env **new_export)
{
	t_line_data	*line_data; // a pointer to the first element of the linked list of nodes
	// t_line_data	*tmp; // a temporary pointer to iterate through the linked list
	t_input		*input_node;
	char *input_line;

	(void)new_export;
	(void)mini_env;
	input_node = *new_input_node;
	while (input_node != NULL)
	{
		input_line = input_node->part_line;
		line_data = NULL;
		if (input_line && (ft_strcmp(input_line, "") != 0))
			{
				input_node->cmd_args = ft_split_line(input_line, &line_data, env, new_input_node);
	//			PRINT THE LINKED LIST
	// ############################################################################
			// tmp = line_data;
			// printf("part of whooooooole line is: %s\n", input_node->part_line);
			// printf("command is: %s\n", input_node->cmd_args[0]);
			// while (tmp != NULL) // print the linked list to check if it's working
			// {
			// 	if (tmp->redirctor != NULL)
			// 		printf("redirector is: %s\n", tmp->redirctor);
			// 	if (tmp->after_redirctor != NULL)
			// 		printf("File name is: %s\n", tmp->after_redirctor);
			// 	// if (tmp->expander != NULL)
			// 	// 	printf("expander is: %s\n", tmp->expander);
			// 	if (tmp->command != NULL)
			// 		printf("Command is: %s\n", tmp->command);
			// 	tmp = tmp->next;
			// }
	// // ############################################################################
			// Free the linked list
			// 	while (line_data != NULL)
			// 	{
			// 		tmp = line_data;
			// 		line_data = line_data->next;
			// 		free(tmp);
			// 	}
			// 	free(input_line);
			}
		input_node = input_node->next;
	}
}

void close_fds(t_input **data)
{
	t_input *t;

	t = (*data);
	while (t != NULL)
	{
		if (t->pipe_in > 0)
		{
			close(t->pipe_out);
			close(t->pipe_in);
		}
		t = t->next;
	}
}

void	wait_for_children(t_input **data)
{
	t_input *t;

	t = (*data);
	while (t != NULL)
	{
		waitpid(t->pro_pid, NULL, 0);
		t = t->next;
	}
}

void	process_execution(t_input **data, char **cmd_args, char **env)
{
	printf("pid in: %d\n", (*data)->write_to_pipe);
	printf("pid out: %d\n", (*data)->read_from_pipe);
	printf("command is: %s\n", (*data)->cmd_args[0]);
	standard_io(data);
	close_fds(data);
	exec_command(cmd_args, env);
	exit(EXIT_SUCCESS);
}

void	fork_and_exec(t_input **data, char **env)
{
	t_input *new_input_node;

	new_input_node = *data;

		while (new_input_node != NULL)
		{
			new_input_node->pro_pid = fork();
			if (new_input_node->pro_pid < 0)
			{
				// eroor_handle
				exit(EXIT_FAILURE);
			}
			if (new_input_node->pro_pid == 0)
			{
				process_execution(&new_input_node, new_input_node->cmd_args, env);
				exit(EXIT_SUCCESS);
			}
			new_input_node = new_input_node->next;
		}
}
