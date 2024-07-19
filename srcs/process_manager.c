/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/19 05:57:15 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_pipes(char *whole_line, t_input **new_input_node);
int	create_input_node(char *whole_line, int i,t_input **new_input_node);
t_input *get_last_node(t_input **node);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);

void	start_prompt(char **env)
{
	char 		*whole_line;
	t_input		*new_input_node;
	t_input		*new_input_node2;
	t_env		*mini_env;
	t_env		*new_export;
	t_input		*t;
	t_input		*t2;

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
	new_input_node2 = new_input_node;
	t = new_input_node;
	t2 = new_input_node;
		start_real_work(&new_input_node, &mini_env, env, &new_export);
		while (new_input_node2 != NULL)
		{
			process_execution(&new_input_node2, new_input_node2->cmd_args, env);
			new_input_node2 = new_input_node2->next;
		}

		while (t2 != NULL)	// wait for the child process to finish
		{
			printf("waiting for pid: %d\n", t2->pro_pid);
			waitpid(t2->pro_pid, NULL ,0);
			t2 = t2->next;
		}
		while (t != NULL)  // close the pipes
		{
			if (t->pipe_in > 0)
			{
				close(t->pipe_in);
				close(t->pipe_out);
			}
			t = t->next;
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


void	start_real_work(t_input **new_input_node, t_env **mini_env, char **env, t_env **new_export)
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

void	process_execution(t_input **data, char **cmd_args, char **env)
{
	t_input *t;
	t_input *t2;

	t= (*data);
	t2= (*data);
	// printf("pid in: %d\n", (*data)->write_to_pipe);
	// printf("pid out: %d\n", (*data)->read_from_pipe);
	(*data)->pro_pid = fork();
	if ((*data)->pro_pid < 0)
	{
		// eroor_handle
		exit(EXIT_FAILURE);
	}
	if ((*data)->pro_pid== 0)
	{
		// printf("process pid is: %d\n", getpid());
		standard_io(data);
		exec_command(cmd_args, env);
		exit(EXIT_SUCCESS);
	}
}
