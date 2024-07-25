/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:46:05 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/25 18:56:12 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (tmp == *data) // if the node  we want to delete is the first node
	{
		*data = tmp->next; // move to the next node
		free(tmp);	// free the node we need to delete
	}
	else
	{
		while (tmp2->next != tmp) //as long as we don't reach the node to delete
			tmp2 = tmp2->next; // move to the next node
		tmp2->next = tmp->next;
		free(tmp);
	}
}

// this function will find the path of the command
// it is just from pipe_x project
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

void	exec_command(char **cmd_args, char **env)
{
	char	*path;

	if (cmd_args[0] != NULL)
		path = find_path(cmd_args[0], env);
	if (execve(path, cmd_args, env) == -1)
		exit(EXIT_FAILURE);
}

char	**merge_free_command(t_line_data **data, int len)
{
	t_line_data	*tmp;
	int			i;
	char		**cmd_args;
	t_line_data	*tmp_delete;

	i = 0;
	tmp = *data;
	cmd_args = (char **)ft_malloc(sizeof(char *) * (len + 1));
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			cmd_args[i] = ft_strdup(tmp->command);
			i++;
			tmp_delete = tmp;
			tmp = tmp->next;
			free(tmp_delete->command);
			delete_node(data, tmp_delete);
		}
		else
		{
			tmp = tmp->next;
		}
	}
	cmd_args[i] = NULL;
	i = 0;
	return (cmd_args);
}

int	cmd_args_counter(t_line_data **data)
{
	int			counter;
	t_line_data	*tmp;

	counter = 0;
	tmp = *data;
	while (tmp != NULL)
	{
		if (tmp->type == 0)
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

char	**command_merge(t_line_data **data)
{
	char		**cmd_args;
	t_line_data	*tmp;

	tmp = *data;
	cmd_args = merge_free_command(data, cmd_args_counter(data));
	return (cmd_args);
}
