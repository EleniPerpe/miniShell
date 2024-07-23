/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fork_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:57:17 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/23 23:28:27 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
