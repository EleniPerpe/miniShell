/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/04 18:27:28 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_execution(t_line_data **data, char **env)
{
	t_line_data *line_data;

	line_data = *data;
			standard_IO(line_data);
			exec_command(line_data, env);
}
