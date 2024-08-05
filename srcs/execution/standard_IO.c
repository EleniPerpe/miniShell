/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_IO.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 07:21:24 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/04 13:46:35 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_outfile(t_line_data *data, char c)
{
	int	fd;

	if (c == 'T')
	{
		fd = open(data->after_redirctor, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (c == 'A')
	{
		fd = open(data->after_redirctor, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

int	open_infile(t_line_data *data, t_env **mini_env)
{
	int	fd;

	fd = open(data->after_redirctor, O_RDONLY);
	if (fd < 0)
	{
		write(2,"minishell: ", 11);
		write(2,data->after_redirctor,ft_strlen(data->after_redirctor));
		write (2 ,": No such file or directory\n", ft_strlen(": No such file or directory\n"));
		change_status(mini_env, 1);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_redirectors(t_input *data, t_env **mini_env)
{
	t_line_data	*current_data;
	t_line_data	*next_data;

	current_data = data->data_node;
	while (current_data != NULL)
	{

		if (current_data->type == 5 || current_data->type == 4 || current_data->type == 3)
			next_data = current_data->next;
		if (current_data->type == 5)
		{
			if (open_infile(next_data, mini_env) != 0)
				return (1);
		}
		else if (current_data->type == 4)
			open_outfile(next_data, 'T');
		else if (current_data->type == 3)
			open_outfile(next_data, 'A');
		current_data = current_data->next;
	}
	return (0);
}
int	standard_io(t_input *data, int **pipe_fd, int i, int processes_num, t_env **mini_env)
{
	if (i == 0 && pipe_fd[i] != NULL)
	{
		close(pipe_fd[i][0]);
		dup2(pipe_fd[i][1], STDOUT_FILENO);
		close(pipe_fd[i][1]);
	}
	else if (i != 0 && i == (processes_num - 1) && pipe_fd[i - 1] != NULL)
	{
		close(pipe_fd[i - 1][1]);
		dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		close(pipe_fd[i - 1][0]);
	}
	else if (i > 0 && i < (processes_num - 1))
	{
			close(pipe_fd[i - 1][1]);
			dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			close(pipe_fd[i - 1][0]);
			close(pipe_fd[i][0]);
			dup2(pipe_fd[i][1], STDOUT_FILENO);
			close(pipe_fd[i][1]);
	}
	if (handle_redirectors(data, mini_env) != 0)
		return (1);
	return (0);
}
