/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:46:05 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/11 17:06:00 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

// // we will use this function to free the allocated memory
// // after execute the command
// void	ft_free(char **paths_spleted, char *cmd, char *path)
// {
// 	int	i;

// 	i = 0;
// 	if (cmd != 0)
// 		free (cmd);
// 	if (path != 0)
// 		free (path);
// 	while (paths_spleted[i] != 0)
// 	{
// 		free (paths_spleted[i]);
// 		i++;
// 	}
// 	if (paths_spleted != 0)
// 		free (paths_spleted);
// }

// void	delete_node(t_line_data **data, t_line_data *tmp)
// {
// 	t_line_data	*tmp2;

// 	tmp2 = *data;
// 	if (tmp == *data) // if the node  we want to delete is the first node
// 	{
// 		*data = tmp->next; // move to the next node
// 		free(tmp);	// free the node we need to delete
// 	}
// 	else
// 	{
// 		while (tmp2->next != tmp) //as long as we don't reach the node to delete
// 			tmp2 = tmp2->next; // move to the next node
// 		tmp2->next = tmp->next;
// 		free(tmp);
// 	}
// }

// this function will find the path of the command
// it is just from pipe_x project
// char	*find_path(char *cmd, char **env)
// {
// 	char	*paths;
// 	char	**paths_spleted;
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	while (ft_strnstr(*env, "PATH", 4) == NULL)
// 		env++;
// 	paths = (*env + 5);
// 	paths_spleted = ft_split(paths, ':');
// 	cmd = ft_strjoin("/", cmd);
// 	while (paths_spleted[i])
// 	{
// 		path = ft_strjoin(paths_spleted[i], cmd);
// 		if (access(path, F_OK | X_OK | R_OK) == 0)
// 		{
// 			ft_free(paths_spleted, cmd, NULL);
// 			return (path);
// 		}
// 		i++;
// 	}
// 	ft_free(paths_spleted, cmd, path);
// 	return (NULL);
// }

// void	exec_command(t_line_data *line_data, char **env)
// {
// 	char	*path;

// 	while (line_data)
// 	{
// 		if (line_data->type == 0)
// 		{
// 			path = find_path(line_data->command, env);
// 			if (execve(path, line_data->command, env) == -1)
// 				exit(EXIT_FAILURE);
// 		}
// 		line_data = line_data->next;
// 	}
// }

// void	merage_free_command(t_line_data **data, int len)
// {

// /*
// 	if we enter the following command:
// 	cat < file -v -n
// 	we will have the following nodes:
// 	node1:		"cat"			type = 0
// 	node2:		"<"				type = 5
// 	node3:		"file"			type = 7
// 	node4:		"-v"	"-n"	type = 0

// 	we need to merge the command and the arguments in one node
// 	so first we will move from node to node search for the type 0
// 	we will put all the data in one string
// 	str = "cat -v -n"
// 	then we will split the string by space and put the data in the nodes
// 	node:	"cat"		"-v"		"-n"		type = 0
// 			cmd			arg[0]		arg[1]

// */

// 	t_line_data	*tmp;
// 	int			i;
// 	char		*str;
// 	t_line_data	*tmp_delete;

// 	tmp = *data;
// 	str = NULL;
// 	str = (char *)ft_malloc(len + 1); // we put everything in one string
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == 0)
// 		{
// 			if (str != NULL) // if the string is not empty that means we
// 			// have data from the previous node so we need to add space
// 				ft_strlcat(str, " ", ft_strlen(str) + 2);
// 			i = 0;
// 			while (tmp->command[i] != NULL)
// 			{
// 				// below we add the command and the arguments from the current node to the string
// 				ft_strlcat(str, tmp->command[i], ft_strlen(str) + ft_strlen(tmp->command[i]) + 1);
// 				if (tmp->command[i + 1] != NULL) // if there is another argument we need to add space
// 					ft_strlcat(str, " ", ft_strlen(str) + 2);
// 				i++;
// 			}
// 			tmp_delete = tmp;
// 			// delete the current node because now we have all the data in str
// 			ft_free(tmp->command, NULL, NULL);
// 			delete_node(data, tmp_delete);
// 		}
// 		tmp = tmp->next; // repeat the process for the next node
// 	}
// 	// now all the data from all nodes type command is in str
// 	// now we need to split the string by space and put the data in the nodes
// 	// and we already have the function for that
// 	// so command_fill() will split and initialize the node we need
// 	command_fill(str, 0, data);
// }

// void	command_merage(t_line_data **data)
// {
// 	// in this function we will merge the command and all arguments in the
// 	// one new node
// 	// and we will free alllll the other nodes
// 	t_line_data	*tmp;
// 	int			i;
// 	int			j;
// 							// we will put everythig in one string
// 							// then we will split it by space
// 	int			space_counter; // ot count how many spaces we need to separate the command and the arguments
// 	int			char_counter; // to count how many characters we need to allocate memory for

// 	j = 0;
// 	space_counter = -1; // -1 because if one command we don't need to add space
// 	char_counter = 0;
// 	tmp = *data;
// 	while (tmp != NULL)
// 	{
// 		i = 0;
// 		if (tmp->type == 0) // if the current node is a command
// 		{
// 			while (tmp->command[i] != NULL)
// 			{
// 				j = 0;
// 				space_counter++; // we need to add space after each argument
// 				while (tmp->command[i][j++] != '\0')
// 					char_counter++; // count the number of characters in the command and the arguments
// 				i++; // move to the next argument in this node
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	merage_free_command(data, char_counter + space_counter); // cahr_counter + space_counter is the length of
// 							// the command and the arguments which we need to allocate memory for
// }
