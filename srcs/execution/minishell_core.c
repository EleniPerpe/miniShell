/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 04:10:28 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/12 04:10:29 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_both_linked_lists(t_input **data, t_env **mini_env, int *processes_num,
		t_inout inout_main)
{
	char	*whole_line;
	int		return_value;

	reset_io(inout_main);
	whole_line = ft_readline();
	*processes_num = split_pipes(whole_line, data, mini_env);
	return_value = init_linked_list(data, mini_env);
	free (whole_line);
	return (return_value);
}

void	start_prompt(t_env **mini_env, t_env **new_export, t_inout inout_main)
{
	t_input		*new_input_node;
	int			processes_num;
	int			check_builtin;

	new_input_node = NULL;
	while (1)
	{
		if ((init_both_linked_lists(&new_input_node, mini_env,
					&processes_num, inout_main) == 0) && (processes_num != -1))
		{
			if ((new_input_node) && (new_input_node->cmd_args[0] != NULL))
				check_builtin = check_for_builtins(new_input_node->cmd_args,
						mini_env, new_export);
			if (processes_num == 1 && check_builtin != -2
				&& check_builtin != 127)
				handle_one_builtin(&new_input_node, mini_env, new_export);
			else if (check_builtin != 127)
				execute_with_pipes(&new_input_node, processes_num,
					mini_env, new_export);
			free_nul(&new_input_node);
		}
		else
			free_nul(&new_input_node);
	}
}
