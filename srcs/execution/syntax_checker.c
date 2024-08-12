/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 03:23:46 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/12 19:09:03 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_syntax(const char *str)
{
	int		len;
	int		i;
	bool	prev_was_pipe;

	i = 0;
	prev_was_pipe = false;
	len = strlen(str);
	if (len == 0)
		return (0);
	while (i < len)
	{
		if (str[i] == '|')
		{
			if (i == 0 || i == len - 1 || prev_was_pipe)
				return (-1);
			prev_was_pipe = true;
		}
		else if (str[i] != ' ')
			prev_was_pipe = false;
		i++;
	}
	if (prev_was_pipe)
		return (-1);
	else
		return (0);
}

int	check_qoute_syntax(char *str)
{
	int	i;
	int	counter;
	int	counter2;

	i = 0;
	counter = 0;
	counter2 = 0;
	while (str[i])
	{
		if (str[i] == '"' && (counter2 % 2 == 0))
			counter++;
		if (str[i] == '\'' && (counter % 2 == 0))
			counter2++;
		i++;
	}
	if (counter % 2 != 0)
		return (-1);
	if (counter2 % 2 != 0)
		return (-1);
	return (0);
}

int	check_spaces_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

int	check_syntax(char *str, t_env **mini_env)
{
	int	checker;

	checker = 0;
	if (check_pipe_syntax(str) == -1)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		change_status(mini_env, 258);
		checker = -1;
	}
	if (check_qoute_syntax(str) == -1)
	{
		printf("The program does not interpret unclosed quotes\n");
		change_status(mini_env, 127);
		checker = -1;
	}
	if (check_spaces_syntax(str) == -1)
	{
		change_status(mini_env, 0);
		checker = -1;
	}
	return (checker);
}
