/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:46:05 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/03 08:57:35 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

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
