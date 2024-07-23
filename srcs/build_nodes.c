/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:45:17 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/23 20:49:16 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	add_inputnode_tolist(t_input **data, t_input *new_line_data)
{
	t_input	*tmp;

	tmp = *data;
	if (*data == NULL)
		*data = new_line_data;
	else
	{
		tmp = *data;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_line_data;
	}
}

int	create_input_node(char *whole_line, int i,t_input **new_input_node)
{
	t_input	*tmp;
	int		j;

	j = 0;
	tmp = (t_input *)ft_malloc(sizeof(t_input));
	while (whole_line[i + j] != '\0' && whole_line[i + j] != '|')
		j++;
	tmp->part_line = (char *)ft_malloc(j + 1);
	tmp->part_line = ft_memcpy(tmp->part_line, &whole_line[i], j);
	tmp->part_line[j] = '\0';
	tmp->next = NULL;
	tmp->data_node = NULL;
	tmp->read_from_pipe = -99;
	tmp->write_to_pipe = -99;
	tmp->pipe_in = -99;
	tmp->pipe_out = -99;
	add_inputnode_tolist(new_input_node, tmp);
	return (i + j);
}

int	split_pipes(char *whole_line, t_input **new_input_node)
{
	int		i;
	int		processes_num;

	i = 0;
	processes_num = 0;
	while (whole_line[i] != '\0')
	{
		if (whole_line[i] == '|')
			i++;
		else
		{
			processes_num++;
			i = create_input_node(whole_line, i, new_input_node);
		}
	}
return (processes_num);
}
void	init_linked_list(t_input **new_input_node, t_env **mini_env, char **env, t_env **new_export)
{
	t_input		*input_node;
	char *input_line;

	(void)new_export;
	(void)mini_env;
	input_node = *new_input_node;
	while (input_node != NULL)
	{
		input_line = input_node->part_line;
		if (input_line && (ft_strcmp(input_line, "") != 0))
			{
				input_node->cmd_args = ft_split_line(input_line, /*&line_data,*/ env, input_node);
			}
		input_node = input_node->next;
	}
}
