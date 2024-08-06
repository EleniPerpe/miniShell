/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:34:32 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/15 14:21:40 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	after_redi_len(char *line, int i)
{
	int		len;

	len = 0;
	if (line[i] == '"' || line[i] == '\'' || line[i] == '\\')
		return (1);
	else
	{
		while (line[i] != ' ' && line[i] != '\0' && line[i] != '"'
			&& line[i] != '\'' && line[i] != '\\')
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	heredoc_init(char *line, int i, t_line_data **data)
{
	int			fd;
	char		*file;
	char		*in_put;

	file = "Libft/tmp_file";
	while (line[i] == ' ')
		i++;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	in_put = readline(">");
	if (in_put != NULL)
	{
		while (ft_strncmp(in_put, &line[i], after_redi_len(line, i)) != 0)
		{
			write (fd, in_put, ft_strlen(in_put));
			write (fd, "\n", 1);
			in_put = readline(">");
			if (in_put == NULL)
				break ;
		}
	}
	fd = after_redirection_fill(line, i, data);
	return (fd);
}
