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

int	after_heredoc_fill(char *line, int i, t_line_data **data)
{
	t_line_data	*new_line_data;
	int			j;

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i + j] != ' ' && line[i + j] != '\0' && line[i + j] != '\''
		&& line[i + j] != '"' && line[i + j] != '>' && line[i + j] != '<')
		j++;
	new_line_data->after_redirctor = ft_strdup("Libft/tmp_file");
	new_line_data->type = 7;
	new_line_data->next = NULL;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	printf("herdoc is: %s\n", new_line_data->after_redirctor );
	add_node_to_list(data, new_line_data);
	return (i + j);
}

int	heredoc_init(char *line, int i, t_line_data **data)
{
	int			fd;
	char		*file;
	char		*in_put;

	file = "Libft/tmp_file";
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return(i);
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
	fd = after_heredoc_fill(line, i, data);
	return (fd);
}
