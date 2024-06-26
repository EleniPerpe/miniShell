/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:42:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/04/09 12:55:42 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

char	*get_next_line(int fd)
{
	int				read_chars;
	char			*buffer;
	char			*next_line;
	static char		*sub;
	char			*temp;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_chars = 1;
	while (read_chars > 0)
	{
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars == -1)
			return (free(sub), free(buffer), sub = NULL, buffer = NULL, NULL);
		buffer[read_chars] = '\0';
		if (check_line(&temp, &sub, &buffer, &next_line) != 0)
			return (next_line);
	}
	if (sub_check(&buffer, &sub, &next_line))
		return (free(sub), sub = NULL, next_line);
	return (free(sub), sub = NULL, next_line);
}

char	*check_line(char **temp, char **sub, char **buffer, char **next_line)
{
	int	i;

	(*temp) = ft_strjoin((*sub), (*buffer));
	if (!(*temp))
		return (NULL);
	free((*sub));
	(*sub) = NULL;
	(*sub) = (*temp);
	i = 0;
	while ((*sub)[i] != '\0' && (*sub)[i] != '\n')
		i++;
	if ((*sub)[i] == '\n')
	{
		(*next_line) = ft_substr((*sub), 0, i + 1);
		(*temp) = ft_substr((*sub), i + 1, ft_strlen((*sub)) - i);
		free((*sub));
		(*sub) = NULL;
		(*sub) = (*temp);
		free ((*buffer));
		(*buffer) = NULL;
		return ((*next_line));
	}
	return ((*next_line));
}

char	*sub_check(char **buffer, char **sub, char **next_line)
{
	free((*buffer));
	(*buffer) = NULL;
	if ((*sub) != NULL && *(*sub) != '\0')
	{
		(*next_line) = ft_strdup((*sub));
		free((*sub));
		(*sub) = NULL;
		return ((*next_line));
	}
	return ((*next_line));
}
