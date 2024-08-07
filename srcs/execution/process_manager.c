/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/06 13:21:33 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_readline()
{
	char *whole_line;

	whole_line = readline("minishell >");
	if (!whole_line) // EOF : ctrl+D
	{
		printf("exit\n");
		exit (EXIT_FAILURE) ;
	}
	if(is_empty(whole_line))
		add_history(whole_line);
	return (whole_line);
}

void	execute_with_pipes(t_input **input_node, int processes_num, t_env **mini_env, t_env **new_export)
{
	int		**pro_pid;
	int		**pipe_fd;
	t_input	*new_input_node;
	t_envexpo	exe_envexport;
	int		i;

	i = 0;
	exe_envexport.exe_env = mini_env;
	exe_envexport.exe_export = new_export;
	new_input_node = *input_node;
	pipe_fd =  pipes_init(processes_num);
	pro_pid  = pid_init(processes_num);
	while (i < processes_num)
	{
		if (fork_and_exec(new_input_node, pro_pid[i], pipe_fd, exe_envexport) != 0)
			exit(EXIT_FAILURE);
		new_input_node = new_input_node->next;
		i++;
	}
	close_fds(pipe_fd);
	wait_for_children(pro_pid, processes_num, mini_env);
	free_all(&new_input_node, pro_pid, pipe_fd);
}

void	handle_one_builtin(t_input **new_input_node,t_env **mini_env,t_env **new_export)
{
	int	exit_buildin;
	t_input *current_node;

	current_node = *new_input_node;
	handle_redirectors(current_node, mini_env);
	exit_buildin = execute_builtins(current_node->cmd_args, mini_env, new_export);
	change_status(mini_env, exit_buildin);
}

void	start_prompt(t_env **mini_env, t_env **new_export, t_inout inout_main)
{
	char		*whole_line;
	t_input		*new_input_node;
	int			processes_num;
	int			check_builtin;

	new_input_node = NULL;
	while (1)
	{
		reset_io(inout_main);
		whole_line = ft_readline();
		processes_num =  split_pipes(whole_line, &new_input_node);
		if (init_linked_list(&new_input_node, mini_env, processes_num) == 0 && processes_num != -1)
		{
			if ((new_input_node) && (new_input_node->cmd_args[0] != NULL))
				check_builtin = check_for_builtins(new_input_node->cmd_args, mini_env, new_export);
			if (processes_num == 1 && check_builtin != -2 && check_builtin != 127)
				handle_one_builtin(&new_input_node, mini_env, new_export);
			else if (check_builtin != 127)
				execute_with_pipes(&new_input_node,processes_num,mini_env,new_export);
			new_input_node = NULL;
		}
		else
			new_input_node = NULL;
	}
}


int	process_execution(t_input *data, int **pipe_fd , t_env **mini_env, t_env **new_export)
{
	int processes_num;
	t_input *tmp;
	int		check_builtin;
	int		exit_buildin;

	tmp = data;
	while (tmp->next)
		tmp = tmp->next;
	processes_num = tmp->i + 1;
	if (standard_io(data, pipe_fd, data->i, processes_num, mini_env) != 0 ||
			data->cmd_args[0] == NULL)
		return (1);
	close_fds(pipe_fd);
	check_builtin = check_for_builtins(data->cmd_args, mini_env, new_export);
	if (check_builtin != -2)
	{
		exit_buildin = execute_builtins(data->cmd_args, mini_env, new_export);
		change_status(mini_env, exit_buildin);
		exit (exit_buildin);
	}
	else if (check_builtin == -2)
	{
		if (exec_command(data->cmd_args, mini_env) != 0)
			return (1);
	}
	return(0);
}

int	fork_and_exec(t_input *data, int *process_pid, int **pipe_fd, t_envexpo exe_envexport)
{

	t_input *new_input_node;
	int		*cur_pro_pid;

	cur_pro_pid = process_pid;
	new_input_node = data;
	setup_signal_exe();
	if ((data->cmd_args[0] != NULL) && (!ft_strncmp(data->cmd_args[0], "exit", 4)))
	{
		modify_shlvl(exe_envexport.exe_env, '-');
		ft_exit(data->cmd_args);
	}
	cur_pro_pid[0] = fork();
	if (cur_pro_pid[0] < 0)
	{
		// eroor_handle
		exit(EXIT_FAILURE);
	}
	else if (cur_pro_pid[0]== 0)
	{
		if (process_execution(new_input_node, pipe_fd, exe_envexport.exe_env, exe_envexport.exe_export) != 0)
			return (1);
	}
	return (0);
}
