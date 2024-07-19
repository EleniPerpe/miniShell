/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_IO.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 07:00:37 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/19 07:12:44 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	standard_io(t_input **data)
{
	int			fd;
	t_line_data	*new_line_data;

	new_line_data = (*data)->data_node;
	if ((*data)->write_to_pipe > 0)
	{
		close((*data)->read_from_pipe);
		dup2((*data)->write_to_pipe, STDOUT_FILENO);
		close((*data)->write_to_pipe);
	}
	if ((*data)->read_from_pipe > 0)
	{
		close((*data)->write_to_pipe);
		dup2((*data)->read_from_pipe, STDIN_FILENO);
		close((*data)->read_from_pipe);
	}
	printf("pid in: %d\n", (*data)->write_to_pipe);
	printf("pid out: %d\n", (*data)->read_from_pipe);
	printf("command is: %s\n", (*data)->cmd_args[0]);
	while (new_line_data != NULL)
	{
		if (new_line_data->redirctor != NULL)
		{
			if (!ft_strcmp("< ", new_line_data->redirctor))
			{
				new_line_data = new_line_data->next;
				fd = open(new_line_data->after_redirctor, O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if (!ft_strcmp(">", new_line_data->redirctor))
			{
				new_line_data = new_line_data->next;
				fd = open(new_line_data->after_redirctor, O_WRONLY | O_CREAT | O_TRUNC, 0777);	//O_WRONLY: the file is opened for writing only.
																						// O_CREAT: to create the file if it does not already exist.
																						// O_TRUNC: clearing any existing content in the file.
																						// 0644: the file permission.
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			else if (!ft_strcmp(">>", new_line_data->redirctor))
			{
				new_line_data = new_line_data->next;
				fd = open(new_line_data->after_redirctor, O_WRONLY | O_CREAT | O_APPEND, 0777); // O_APPEND: the file is opened in append mode.
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			// to be continued:
			// else if (!ft_strcmp(new_line_data->redirctor, "<<"))
			// {
			// }
		}
		else
			new_line_data = new_line_data->next;
	}
}

void	reset_io(void)
{
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}
