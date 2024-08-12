/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:52:28 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/09 00:52:29 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char **paths_spleted, char *cmd, char *path)
{
	int	i;

	i = 0;
	if (cmd != 0)
		free (cmd);
	if (path != 0)
		free (path);
	while (paths_spleted[i] != 0)
	{
		free (paths_spleted[i]);
		i++;
	}
	if (paths_spleted != 0)
		free (paths_spleted);
}

void	delete_node(t_line_data **data, t_line_data *tmp, char *str)
{
	t_line_data	*tmp2;

	tmp2 = *data;
	if (tmp == *data)
	{
		*data = tmp->next;
		free(tmp);
	}
	else
	{
		while (tmp2->next != tmp)
			tmp2 = tmp2->next;
		tmp2->next = tmp->next;
		free(tmp);
	}
	if (str)
		free (str);
}

char	*ft_readline(void)
{
	char	*whole_line;

	whole_line = readline("minishell >");
	if (!whole_line)
	{
		printf("exit\n");
		exit (EXIT_FAILURE);
	}
	if (is_empty(whole_line))
		add_history(whole_line);
	return (whole_line);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	free_str(char *temp, char *line1, char *line2, char *cmp_temp)
{
	free(temp);
	if (line1)
		free(line1);
	if (line2)
		free(line2);
	free(cmp_temp);
}
