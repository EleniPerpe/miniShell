/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:46:05 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/07 19:17:40 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path(char *cmd, char **env)
{
	char	*paths;
	char	**path_splitted;
	char	*path;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while ((*env) && (ft_strnstr(*env, "PATH", 4) == NULL))
		env++;
	if (*env)
	{
		paths = (*env + 5);
		path_splitted = ft_split(paths, ':');
		cmd = ft_strjoin("/", cmd);
		while (path_splitted[i])
		{
			path = ft_strjoin(path_splitted[i++], cmd);
			if (access(path, F_OK | X_OK | R_OK) == 0)
				return (ft_free(path_splitted, cmd, NULL), path);
			free(path);
		}
		ft_free(path_splitted, cmd, NULL);
	}
	return (NULL);
}

void	create_cmd(char **cmd_args)
{
	char	*cmd;
	char	*cmd_only;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = *cmd_args;
	len = ft_strlen(cmd);
	while (cmd[i] != '\0')
		i++;
	i--;
	while (cmd[i] != '/')
		i--;
	cmd_only = (char *)ft_malloc(len - i + 1);
	i++;
	while (cmd[i] != '\0')
		cmd_only[j++] = cmd[i++];
	cmd_only[j] = '\0';
	free(*cmd_args);
	*cmd_args = cmd_only;
}

char	*handle_path_cmd(char **cmd_args)
{
	int		i;
	int		len;
	char	*cmd;
	char	*path;

	i = 0;
	cmd = *cmd_args;
	len = ft_strlen(cmd);
	while (cmd[i] != '\0' && cmd[i] != '/')
		i++;
	if (i != len)
	{
		path = ft_strdup(*cmd_args);
		create_cmd(cmd_args);
		return (path);
	}
	return (NULL);
}

void	ft_execve(char *path, char **cmd_args, t_env **mini_env, char **env)
{
	if (execve(path, cmd_args, env) == -1)
	{
		free(path);
		printf("minishell: %s: command not found\n", cmd_args[0]);
		change_status(mini_env, 127);
		exit (127);
	}
}

int	exec_command(char **cmd_args, t_env **mini_env)
{
	char	*path;
	char	**env;

	env = minienv_to_env(mini_env);
	path = handle_path_cmd(cmd_args);
	if (!path)
	{
		if (cmd_args[0] != NULL)
			path = find_path(cmd_args[0], env);
		if (path == NULL && cmd_args[0] != NULL)
			path = ft_strjoin("./", cmd_args[0]);
		ft_execve(path, cmd_args, mini_env, env);
	}
	ft_execve(path, cmd_args, mini_env, env);
	return (0);
}
