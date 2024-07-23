/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/23 19:52:46 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		split_pipes(char *whole_line, t_input **new_input_node);
int		create_input_node(char *whole_line, int i,t_input **new_input_node);
t_input	*get_last_node(t_input **node);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);
void	close_fds(int **pipe_fd);
void	wait_for_children(int **pro_pid, int processes_num);
void	fork_and_exec(t_input *data, char **env, int *process_pid, int **pipe_fd, int i, int processes_num); // 6 args!!
int		**pipes_init(int processes_num);
// void	assign_pipe_to_nodes(t_input **data, int **pipe_fd, int process_num);
void	start_prompt(char **env)
{
	char 		*whole_line;
	t_input		*new_input_node;
	t_env		*mini_env;
	t_env		*new_export;
	int			processes_num;
	int			**pro_pid;
	int			**pipe_fd;
	int i;

	i = 0;
	mini_env = NULL;
	new_input_node = NULL;
	create_path(env, &mini_env);
	new_export = NULL;
	create_export_path(&mini_env, &new_export);
	while (1)
	{
		reset_io(); // need to modify it to take STD IN and OUT from before the while
		whole_line = readline("minishell >");
		add_history(whole_line);
		processes_num =  split_pipes(whole_line, &new_input_node);

		init_linked_list(&new_input_node, &mini_env, env, &new_export);
		pipe_fd =  pipes_init(processes_num);
		pro_pid = (int **)ft_malloc(sizeof(int *) * (processes_num + 1));
		pro_pid[processes_num] = NULL;
		while (i < processes_num)
		{
			pro_pid[i] = (int *)ft_malloc(sizeof(int) * 2);
			pro_pid[i][1] = (int)NULL;
			fork_and_exec(new_input_node, env, pro_pid[i], pipe_fd, i, processes_num);
			new_input_node = new_input_node->next;
			i++;
		}
		close_fds(pipe_fd);
		wait_for_children(pro_pid, processes_num);
		// we need to free everything:
		t_input *line_data;
		t_input *tmp;
		line_data = new_input_node;
		while (line_data != NULL)
		{
			tmp = line_data;
			line_data = line_data->next;
			free(tmp);
		}
		free(new_input_node);
		free(whole_line);
		int k = 0;
		while (pro_pid[k] != NULL)
		{
			free(pro_pid[k]);
			k++;
		}
		free(pro_pid);
		k = 0;
		while (pipe_fd[k] != NULL)
		{
			free(pipe_fd[k]);
			k++;
		}
		free(pipe_fd);
	}
}

int	split_pipes(char *whole_line, t_input **new_input_node)
{
	int		i;
	int		processes_num;

	i = 0;
	processes_num = 0;
	while (whole_line[i] != '\0')
	{
		if (whole_line[i] == '|')
			i++;
		else
		{
			processes_num++;
			i = create_input_node(whole_line, i, new_input_node);
		}
	}
return (processes_num);
}

int	create_input_node(char *whole_line, int i,t_input **new_input_node)
{
	t_input	*tmp;
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
	t_input		*input_node;
	char *input_line;

	(void)new_export;
	(void)mini_env;
	input_node = *new_input_node;
	while (input_node != NULL)
	{
			printf("check check\n");
		input_line = input_node->part_line;
		if (input_line && (ft_strcmp(input_line, "") != 0))
			{
				input_node->cmd_args = ft_split_line(input_line, /*&line_data,*/ env, input_node);
	//			PRINT THE LINKED LIST
	// ############################################################################
			// t_line_data *tmp;

			// tmp = input_node->data_node;
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
	// // // ############################################################################
			}
		input_node = input_node->next;
	}
}

void close_fds(int **pipe_fd)
{
	int i;

	i = 0;
	while (pipe_fd[i] != NULL)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	wait_for_children(int **pro_pid, int processes_num)
{
	int i;
	i = 0;
	while (i < processes_num)
	{
		waitpid(pro_pid[i][0] , NULL, 0);
		i++;
	}
}

void	process_execution(t_input *data, char **env, int **pipe_fd, int i, int processes_num)
{
	standard_io(data, pipe_fd, i, processes_num);
	close_fds(pipe_fd);
	exec_command(data->cmd_args, env);
	exit(EXIT_SUCCESS);
}

void	fork_and_exec(t_input *data, char **env, int *process_pid, int **pipe_fd, int i, int processes_num)
{
	t_input *new_input_node;
	int		*cur_pro_pid;

	cur_pro_pid = process_pid;
	new_input_node = data;
	cur_pro_pid[0] = fork();
	if (cur_pro_pid[0] < 0)
	{
		// eroor_handle
		exit(EXIT_FAILURE);
	}
	else if (cur_pro_pid[0]== 0)
	{
		process_execution(new_input_node, env, pipe_fd, i, processes_num);
		exit(EXIT_SUCCESS); // not necessary
	}
}
int **pipes_init(int processes_num)
{
	int		**pipe_fd;
	int		i;

	i = 0;
	pipe_fd = (int **)ft_malloc(sizeof(int *) * (processes_num - 1 + 1));
	pipe_fd[processes_num - 1] =NULL;
	while (i < (processes_num - 1))
	{
		pipe_fd[i] = (int *)ft_malloc(sizeof(int) * 2);
		pipe(pipe_fd[i]);
		i++;
	}
	return (pipe_fd);
}
