/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:45:17 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/12 19:01:45 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_inputnode_tolist(t_input **data, t_input *new_line_data)
{
	t_input	*tmp;

	tmp = *data;
	if (*data == NULL)
		*data = new_line_data;
	else
	{
		tmp = *data;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_line_data;
	}
}

int	create_input_node(char *whole_line, int i, t_input **new_input_node, int k)
{
	t_input	*tmp;
	int		j;
	char	*res;

	j = 0;
	tmp = (t_input *)ft_malloc(sizeof(t_input));
	while (whole_line[i + j] != '\0')
	{
		if (whole_line[i + j] == '|')
		{
			res = ft_substr(whole_line, i, i + j);
			if (check_qoute_syntax(res) == -1)
				;
			else
				break ;
			free(res);
		}
		j++;
	}
	tmp->part_line = (char *)ft_malloc(j + 1);
	tmp->part_line = ft_memcpy(tmp->part_line, &whole_line[i], j);
	tmp->next = NULL;
	tmp->data_node = NULL;
	tmp->i = k;
	return (add_inputnode_tolist(new_input_node, tmp), i + j);
}

int	split_pipes(char *whole_line, t_input **new_input_node, t_env **mini_env)
{
	int		i;
	int		j;
	int		processes_num;

	i = 0;
	j = 0;
	(void)mini_env;
	processes_num = 0;
	if (!whole_line)
		return (0);
	if (check_syntax(whole_line, mini_env) == -1)
		return (-1);
	while (whole_line[i] != '\0')
	{
		if ((whole_line[i] == '|') && (whole_line[i + 1] != '|'))
			i++;
		else
		{
			processes_num++;
			i = create_input_node(whole_line, i, new_input_node, j++);
		}
	}
	return (processes_num);
}

int	init_linked_list(t_input **new_input_node, t_env **mini_env)
{
	t_input	*input_node;
	char	*input_line;

	input_node = *new_input_node;
	while (input_node != NULL)
	{
		input_line = input_node->part_line;
		if ((input_line == NULL) || !(is_empty(input_line)))
		{
			input_node = NULL;
			return (1);
		}
		if (input_line != NULL && (ft_strcmp(input_line, "") != 0))
		{
			input_node->cmd_args = ft_split_line(input_line,
					mini_env, input_node);
			if (input_node->cmd_args == NULL)
				return (1);
		}
		input_node = input_node->next;
	}
	return (0);
}
