/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:34:32 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/12 00:46:42 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	after_redi_len(char *line, int i)
{
	int		len;

	len = 0;
	while (line[i] != ' ' && line[i] != '\0' && line[i] != '|'
		&& line[i] != '<' && line[i] != '>')
	{
		i++;
		len++;
	}
	return (len);
}

int	heredoc_init(char *line, int i, t_line_data **data)
{
	int			fd;
	// t_line_data	*new_line_data;
	char		*file;
	char		*in_put;

	file = "Libft/tmp_file";
	// new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		//error_handle function
	}
	in_put = readline(">");
	while (ft_strncmp(in_put, &line[i], after_redi_len(line, i)) != 0)
	{
		write (fd, in_put, ft_strlen(in_put));
		write (fd, "\n", 1);
		in_put = readline(">");
	}
	if (close(fd) == -1)
	{
		// error_handle function
	}
	fd = after_redirection_fill(line, i, data);
	return (5);
}
