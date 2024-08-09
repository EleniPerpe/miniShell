/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:05 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 18:36:52 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quotes_command(char *line, int j, t_line_data **data);
int		check_quotes_cases(char *line, int *i);
int		check_for_flag(char *line, int i);
int		check_for_size(char *line, int j, int *i, char c);

int	quote_token(char *line, int i, t_line_data **line_data, int j)
{
	int		flag;
	char	*tmp;

	flag = -1;
	flag = check_for_flag(line, i);
	while (line[i] == '"' || line[i] == '\'')
		i++;
	j = check_quotes_cases(line, &i);
	if (j == -1)
		return (j);
	if (j > 0)
	{
		tmp = (char *)ft_malloc(j + 1);
		ft_memcpy(tmp, &line[i], j);
		tmp[j] = '\0';
		if (flag == 7)
			quotes_after_redireciton(tmp, j, line_data);
		else if (flag == 2 || j == -1)
			heredoc_init(line, i, line_data);
		else if (flag == 0)
			quotes_command(tmp, j, line_data);
		free(tmp);
	}
	return (i + j + 1);
}

int	check_for_flag(char *line, int i)
{
	int	flag;

	flag = 0;
	while (i > 0 && (line[i] == ' ' || line[i] == '"' || line[i] == '\''))
		i--;
	if (line[i] == '<' || line[i] == '>')
	{
		if (i > 0 && line[i - 1] == '<')
			flag = 2;
		else
			flag = 7;
	}
	else
		flag = 0;
	i++;
	return (flag);
}

int	check_quotes_cases(char *line, int *i)
{
	int	j;

	j = 0;
	if (*i <= 0)
		return (0);
	(*i)--;
	if (line[*i] == '\'')
		j = check_for_size(line, j, &(*i), '\'');
	else if (line[*i] == '"')
		j = check_for_size(line, j, &(*i), '"');
	return (j);
}

int	check_for_size(char *line, int j, int *i, char c)
{
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i + j] != c && (line[*i + j] != '\0'))
	{
		j++;
	}
	if (line[*i + j] == '\0')
	{
		printf("The program does not interpret unclosed quotes\n");
		return (-1);
	}
	return (j);
}
