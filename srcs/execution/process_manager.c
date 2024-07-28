/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/28 06:24:47 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	start_prompt(char **env, t_env **mini_env, t_env **new_export)
{
	char 		*whole_line;
	t_input		*new_input_node;
	int			processes_num;
	int			**pro_pid;
	int			**pipe_fd;
	int i;
	(void)mini_env;
	(void)new_export;
	new_input_node = NULL;
	while (1)
	{
		i = 0;
		reset_io(); // need to modify it to take STD IN and OUT from before the while
		whole_line = readline("minishell >");
		add_history(whole_line);
		processes_num =  split_pipes(whole_line, &new_input_node);

		init_linked_list(&new_input_node, env);
		pipe_fd =  pipes_init(processes_num);
		pro_pid  = pid_init(processes_num);
		while (i < processes_num)
		{
			fork_and_exec(new_input_node, env, pro_pid[i], pipe_fd, mini_env, new_export);
			new_input_node = new_input_node->next;
			i++;
		}
		close_fds(pipe_fd);
		wait_for_children(pro_pid, processes_num);
		free_all(&new_input_node, pro_pid, pipe_fd); // not done, need a lot of work
	}
}


void	process_execution(t_input *data, char **env, int **pipe_fd , t_env **mini_env, t_env **new_export)
{
	int processes_num;
	t_input *tmp;

	tmp = data;
	while (tmp->next)
		tmp = tmp->next;
	processes_num = tmp->i + 1;
	standard_io(data, pipe_fd, data->i, processes_num);
	close_fds(pipe_fd);
	if (check_for_builtins(data->cmd_args, mini_env, new_export, env) == 0)
		;
	else
		exec_command(data->cmd_args, env);
	exit(EXIT_SUCCESS);
}

void	fork_and_exec(t_input *data, char **env, int *process_pid, int **pipe_fd, t_env **mini_env, t_env **new_export)
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
		process_execution(new_input_node, env, pipe_fd, mini_env, new_export);
		exit(EXIT_SUCCESS); // not necessary
	}
}
