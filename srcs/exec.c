/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:46:05 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/03 22:05:51 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"


// we will use this function to free the allocated memory
// after execute the command
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

void	delete_node(t_line_data **data, t_line_data *tmp)
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
}


char	*find_path(char *cmd, char **env)
{
	char	*paths;
	char	**paths_spleted;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(*env, "PATH", 4) == NULL)
		env++;
	paths = (*env + 5);
	paths_spleted = ft_split(paths, ':');
	cmd = ft_strjoin("/", cmd);
	while (paths_spleted[i])
	{
		path = ft_strjoin(paths_spleted[i], cmd);
		if (access(path, F_OK | X_OK | R_OK) == 0)
		{
			ft_free(paths_spleted, cmd, NULL);
			return (path);
		}
		i++;
	}
	ft_free(paths_spleted, cmd, path);
	return (NULL);
}

void	exec_command(t_line_data *line_data, char **env)
{
	char *path;

	while (line_data)
	{
		if (line_data->type == 0)
		{
			path = find_path(line_data->command[0], env);
			if (execve(path, line_data->command, env) == -1)
			exit(EXIT_FAILURE);
		}
		line_data = line_data->next;
	}
}

void	merage_free_command(t_line_data **data, int len)
{
	t_line_data	*tmp;
	int			i;
	char		*str;
	t_line_data	*tmp_delete;

	tmp = *data;
	str = NULL;
	str = (char *)ft_malloc(len + 1);
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			if (str != NULL)
				ft_strlcat(str, " ", ft_strlen(str) + 2);
			i = 0;
			while (tmp->command[i] != NULL)
			{
				ft_strlcat(str, tmp->command[i], ft_strlen(str) + ft_strlen(tmp->command[i]) + 1);
				if (tmp->command[i + 1] != NULL)
					ft_strlcat(str, " ", ft_strlen(str) + 2);
				i++;
			}
			tmp_delete = tmp;
			ft_free(tmp->command, NULL, NULL);
			delete_node(data, tmp_delete);
		}
		tmp = tmp->next;
	}
	command_fill(str, 0, data);
}

void	command_merage(t_line_data **data)
{
	// in this function we will merge the command and the arguments in the
	// first command node
	// and we will free the other nodes
	t_line_data	*tmp;
	int			i;
	int			j;
	int			space_counter; // ot count how many spaces we need to separate the command and the arguments
	int			char_counter;

	j = 0;
	space_counter = -1; // if one command we don't need to add space
	char_counter = 0;
	tmp = *data;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->type == 0)
		{
			while (tmp->command[i] != NULL)
			{
				j = 0;
				space_counter++;
				while (tmp->command[i][j++] != '\0')
					char_counter++;
				i++;
			}
		}
		tmp = tmp->next;
	}
	merage_free_command(data, char_counter + space_counter); // cahr_counter + space_counter is the length of
							// the command and the arguments which we need to allocate memory for
}
