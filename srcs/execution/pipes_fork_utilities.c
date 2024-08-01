/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fork_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:57:17 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/31 03:40:49 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int **pipes_init(int processes_num)
{
	int		**pipe_fd;
	int		i;

	i = 0;
	if (processes_num == 0)
		return (0);
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
	if (!pipe_fd)
		return ;
	while (pipe_fd[i] != NULL)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	wait_for_children(int **pro_pid, int processes_num, t_env **mini_env)
{
	(void)mini_env;
	int status;
	int i;

	i = 0;
	while (i < processes_num)
	{
		waitpid(pro_pid[i][0] , &status, 0);
		if (WIFEXITED(status))
			change_status(mini_env , WEXITSTATUS(status));
		// if (WIFSIGNALED(status))
		// {
		// 	change_status (mini_env, WTERMSIG(status));
		// 	printf("test test two\n");
		// }
		i++;
	}
	setup_signal_init();
}

int **pid_init(int processes_num)
{
	int	**pro_pid;
	int	i;

	i = 0;
	pro_pid = (int **)ft_malloc(sizeof(int *) * (processes_num + 1));
	pro_pid[processes_num] = NULL;
	while ( i < processes_num)
	{
		pro_pid[i] = (int *)ft_malloc(sizeof(int) * 2);
		pro_pid[i][1] = 0;
		i++;
	}
	return (pro_pid);
}
char **minienv_to_env(t_env **mini_env)
{
	(void)mini_env;
	char	**env;
	int		counter;
	int		i;
	t_env	*tmp_count;
	t_env	*tmp;

	i = 0;
	counter = 0;
	tmp_count = *mini_env;
	tmp = *mini_env;
	while(tmp_count != NULL)
	{
		counter++;
		tmp_count = tmp_count->next;
	}
	env = (char **)ft_malloc(sizeof(char *) * (counter + 1));
	while(i < counter)
	{
		env[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
