/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/12 03:18:33 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	// for each pipe | we will change the standard input and output in both nodes
	// then we will fork and execute the command in child in each node
	// after changing the IO to write and read from the pipe we will change them again inside each node depending on the redirectors in it
	// because redirectors have higher priority than pipes
	// so we must know how many pipes we have
void	process_execution(t_line_data **data, char **cmd_args, char **env)
{
	int	pid;
	t_line_data	*line_data;

	pid = fork();
	if (pid < 0)
	{
		// eroor_handle
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		line_data = *data;
		standard_io(line_data);
		exec_command(cmd_args, env);
	}
	waitpid(pid, 0 ,0);
}
