/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/24 13:11:26 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_other_envs(t_env **mini_env,t_env **new_export, char *line);
void	replace_nodes(t_env **mini_env, char *line, int i, int bool);
char	*create_previous_directory(t_env **mini_env);
void	create_old_pwd(t_env **mini_env, t_env **new_export);
void	check_if_exists(t_env **envs);

void	ft_cd(t_env **mini_env, char **args, char **env, t_env **new_export)
{
	char *new_pwd;
	char *temp_pwd;

	(void)env;
	// create_old_pwd(mini_env, new_export);
	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		temp_pwd = getenv("HOME");
		if (temp_pwd == NULL)
		{
			fprintf(stderr, "Cannot find HOME environment variable\n");
			exit (EXIT_FAILURE);
		}
		// printf("Home : %s\n", temp_pwd);
		if (chdir(temp_pwd) != 0)
		{
			perror("chdir() error");
			exit (EXIT_FAILURE);
		}
	}
	// else if (args[1] != NULL && (ft_strncmp("--", args[1], 2)))
	// {
	// 	//give the oldpwd instead
	// }
	else if (args[1] != NULL || (ft_strncmp("..", args[1], 2)))
	{
		temp_pwd = create_previous_directory(mini_env);
		if (chdir(temp_pwd) != 0)
		{
			perror("chdir() error");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		temp_pwd = args[1];
		if (chdir(temp_pwd) != 0)
		{
			perror("chdir() error");
			exit (EXIT_FAILURE);
		}
	}
	new_pwd = ft_strjoin("PWD=", temp_pwd);
	// printf("New home is : %s\n", new_pwd);
	change_other_envs(mini_env, new_export, new_pwd);

	free(new_pwd);
	// free(old_pwd);
}

	
// void	create_old_pwd(t_env **mini_env, t_env **new_export)
// {
// 	char *old_pwd;
// 	size_t size = 1024;
// 	t_env *pwd_export;
// 	t_env *pwd_env;
	
// 	(void)new_export;
// 	check_if_exists(mini_env);
// 	check_if_exists(new_export);
// 	old_pwd = (char *)ft_malloc(size);
// 	if (getcwd(old_pwd, size) != NULL)
// 	{
// 		pwd_export = (t_env *)ft_malloc(sizeof(t_env));
// 		pwd_export->line = ft_strjoin("OLDPWD=", old_pwd);
// 		pwd_export->next = NULL;
// 		pwd_env = (t_env *)ft_malloc(sizeof(t_env));
// 		pwd_env->line = ft_strjoin("OLDPWD=", old_pwd);
// 		pwd_env->next = NULL;
// 		add_path_to_list(mini_env, pwd_env);

// 	}
// 	else
//         perror("getcwd() error");
// }

// void check_if_exists(t_env **envs)
// {
// 	t_env *temp_envs;
// 	t_env *next_env;
// 	char *temp_export;

// 	temp_envs = *envs;
// 	while (temp_envs != NULL)
// 	{
// 		next_env = temp_envs->next;
// 		printf("Hi from line %s :)\n", temp_envs->line);
// 		if (ft_strncmp("OLDPWD", temp_envs->line, 6) == 0)
// 				node_remove(envs, temp_envs->line, 6);
// 		else if (ft_strncmp("declare -x OLDPWD", temp_envs->line, 17) == 0)
// 		{
// 			printf("Hi :)\n");
// 			temp_export = ft_strjoin("declare -x ", temp_envs->line);
// 			node_remove(envs, temp_export, 6);
// 		}
// 		temp_envs = next_env;
// 	}
// }


char	*create_previous_directory(t_env **mini_env)
{
	t_env *temp;
	char *final;
	int len;
	char *rest;


	temp = *mini_env;
	while (temp != NULL && ft_strncmp("PWD=", temp->line, 4) != 0)
		temp = temp->next;
	rest = ft_strrchr(temp->line, '/');
	len = ft_strlen(temp->line) - ft_strlen(rest);
	final = (char *)ft_malloc(len + 1);
	final = ft_substr(temp->line, 4, len - 4);
	printf("That's the final : %s\n", final);
	return (final);
}


void	change_other_envs(t_env **mini_env,t_env **new_export, char *line)
{
	int i;
	t_env *current_mini_env;
	t_env *current_new_export;
	char *temp_export;
	
	i = 0;
	current_mini_env = *mini_env;
	// printf("Line : %s\n", line);
	while (line[i] != '=' && line[i] != '\0')
		i++;
	while (current_mini_env != NULL && ft_strncmp(current_mini_env->line, line, i) != 0)
		current_mini_env = current_mini_env->next;
	if (current_mini_env != NULL)
		replace_nodes(mini_env, line, i, 1);
	current_new_export = *new_export;
	while (current_new_export != NULL && ft_strncmp(current_new_export->line + 11, line, i) != 0)
		current_new_export = current_new_export->next;
	if (current_new_export != NULL)
	{
		temp_export = ft_strjoin("declare -x ", line);
		replace_nodes(new_export, temp_export, i + 11, 2);
	}
}

void replace_nodes(t_env **mini_env, char *line, int i, int bool)
{
	t_env *temp_env;
	
	// printf("Line :: %s\n", line);
	node_remove(mini_env, line, i);
	temp_env = (t_env *)ft_malloc(sizeof(t_env));
	if (bool == 1)
		temp_env->line = ft_strdup(line);
	else
		temp_env->line = ft_strdup(line);
	temp_env->next = NULL;
	add_path_to_list(mini_env, temp_env);
}