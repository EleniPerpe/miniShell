/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:46:05 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/31 19:41:30 by eperperi         ###   ########.fr       */
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
	if(env != NULL)
	{
		while ((*env) && (ft_strnstr(*env, "PATH", 4) == NULL))
			env++;
		if (*env)
		{
			paths = (*env + 5);
			paths_spleted = ft_split(paths, ':');
			cmd = ft_strjoin("/", cmd);
			while (paths_spleted[i])
			{
				path = ft_strjoin(paths_spleted[i++], cmd);
				if (access(path, F_OK | X_OK | R_OK) == 0)
					return (ft_free(paths_spleted, cmd, NULL),path);
			}
			ft_free(paths_spleted, cmd, path);
		}
	}
	return (NULL);
}

void	create_cmd(char **cmd_args)
{
	char *cmd;
	char *cmd_only;
	int	len;
	int	i;
	int	j;

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
	while(cmd[i] != '\0')
		cmd_only[j++] = cmd[i++];
	cmd_only[j] = '\0';
	free(*cmd_args);
	*cmd_args = cmd_only;
}

char *handle_path_cmd(char **cmd_args)
{
	int	i;
	int	len;
	char	*cmd;
	char	*path;

	i = 0;
	cmd = *cmd_args;
	len = ft_strlen(cmd);
	while (cmd[i] != '\0' && cmd[i] != '/')
		i++;
	if ( i != len)
	{
		path = ft_strdup(*cmd_args);
		create_cmd(cmd_args);
		return (path);
	}
	return (NULL);
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
		if (execve(path, cmd_args, env) == -1)
		{
			printf("minishell: %s: command not found\n", cmd_args[0]);
			change_status(mini_env, 127);
			exit (127);
		}
	}
	if (execve(path, cmd_args, env) == -1)
	{
		printf("minishell: %s: No such file or directory\n", path);
		change_status(mini_env, 127);
		exit (127);
	}
	return (0);
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
			tmp = tmp->next;
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
	// t_line_data	*tmp;

	// tmp = *data;
	cmd_args = merge_free_command(data, cmd_args_counter(data));
	return (cmd_args);
}
