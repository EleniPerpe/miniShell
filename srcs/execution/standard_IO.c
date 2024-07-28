/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_IO.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 05:28:36 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/28 05:28:39 by rshatra          ###   ########.fr       */
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

void	open_infile(t_line_data *data)
{
	int	fd;

	fd = open(data->after_redirctor, O_RDONLY);
	if (fd < 0)
	{
		write(2,"minishell: ", 11);
		write(2,data->after_redirctor,ft_strlen(data->after_redirctor));
		write (2 ,": No such file or directory", ft_strlen(": No such file or directory"));
		// signal to kill the process must ne sent from here
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redirectors(t_input *data)
{
	t_line_data	*current_data;
	t_line_data	*next_data;

	current_data = data->data_node;
	while (current_data != NULL)
	{

		if (current_data->type == 5 || current_data->type == 4 || current_data->type == 3)
			next_data = current_data->next;
		if (current_data->type == 5)
			open_infile(next_data);
		else if (current_data->type == 4)
			open_outfile(next_data, 'T');
		else if (current_data->type == 3)
			open_outfile(next_data, 'A');
		current_data = current_data->next;
	}
}
void	standard_io(t_input *data, int **pipe_fd, int i, int processes_num)
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
	handle_redirectors(data);
}

void	reset_io(void)
{
		int	stand_in;
		int	stand_out;
		stand_in = dup(STDIN_FILENO);
		stand_out = dup(STDOUT_FILENO);

		dup2(stand_in, STDIN_FILENO);
		dup2(stand_out , STDOUT_FILENO);
		close(stand_in);
		close(stand_out);
}
