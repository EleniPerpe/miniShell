/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/23 21:49:49 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		free_all(&new_input_node, pro_pid, pipe_fd); // not done, need a lot of work
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

	(void)i;
	(void)processes_num;

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
