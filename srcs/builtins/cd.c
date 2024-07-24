/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/24 17:54:04 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_other_envs(t_env **mini_env,t_env **new_export, char *line);
void	replace_nodes(t_env **mini_env, char *line, int i);
char	*create_previous_directory(t_env **mini_env);
void	create_old_pwd(t_env **mini_env, t_env **new_export);
void	check_if_exists(t_env **envs);
void	check_and_change_dir(char *dir);

void	ft_cd(t_env **mini_env, char **args, t_env **new_export)
{
	char *new_pwd;
	char *temp_pwd;
	
	create_old_pwd(mini_env, new_export);
	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		temp_pwd = getenv("HOME");
		check_and_change_dir(temp_pwd);
	}
	else if (args[1] != NULL && (ft_strncmp("..", args[1], 2)) == 0)
	{
		temp_pwd = create_previous_directory(mini_env);
		check_and_change_dir(temp_pwd);
	}
	else
	{
		temp_pwd = args[1];
		check_and_change_dir(args[1]);
	}
	new_pwd = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", temp_pwd);
	change_other_envs(mini_env, new_export, new_pwd);
	free(new_pwd);
	free(temp_pwd);
}

void check_and_change_dir(char *dir)
{
	if (dir == NULL)
		fprintf(stderr, "Cannot find environment variable\n");
	if (chdir(dir) != 0)
		perror("chdir() error");
}
	
void create_old_pwd(t_env **mini_env, t_env **new_export)
{
	char *old_pwd;
	size_t size = 1024;
	t_env *pwd_export;
	t_env *pwd_env;
	
	check_if_exists(mini_env);
	check_if_exists(new_export);
	old_pwd = (char *)ft_malloc(size);
	if (getcwd(old_pwd, size) != NULL)
	{
		pwd_export = (t_env *)ft_malloc(sizeof(t_env));
		pwd_export->line = ft_strjoin_export("declare -x OLDPWD=", old_pwd, '"');
		pwd_export->next = NULL;
		add_path_to_list(new_export, pwd_export);
		pwd_env = (t_env *)ft_malloc(sizeof(t_env));
		pwd_env->line = ft_strjoin("OLDPWD=", old_pwd);
		pwd_env->next = NULL;
		add_path_to_list(mini_env, pwd_env);
	}
	else
        perror("getcwd() error");
	free(old_pwd);
}

void check_if_exists(t_env **envs)
{
	t_env *temp_envs;
	t_env *next_env;
	char *temp_export;

	temp_envs = *envs;
	while (temp_envs != NULL)
	{
		next_env = temp_envs->next;
		if (ft_strncmp("OLDPWD", temp_envs->line, 6) == 0)
				node_remove(envs, temp_envs->line, 6);
		else if (ft_strncmp("declare -x OLDPWD", temp_envs->line, 17) == 0)
		{
			temp_export = ft_strjoin("declare -x ", temp_envs->line);
			node_remove(envs, temp_export, 6);
		}
		temp_envs = next_env;
	}
}


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
	while (line[i] != '=' && line[i] != '\0')
		i++;
	while (current_mini_env != NULL && ft_strncmp(current_mini_env->line, line, i) != 0)
		current_mini_env = current_mini_env->next;
	if (current_mini_env != NULL)
		replace_nodes(mini_env, line, i);
	current_new_export = *new_export;
	while (current_new_export != NULL && ft_strncmp(current_new_export->line + 11, line, i) != 0)
		current_new_export = current_new_export->next;
	if (current_new_export != NULL)
	{
		temp_export = ft_strjoin_export("declare -x PWD=", line + 4, '"');
		replace_nodes(new_export, temp_export, i + 11);
	}
}

void replace_nodes(t_env **mini_env, char *line, int i)
{
	t_env *temp_env;
	
	node_remove(mini_env, line, i);
	temp_env = (t_env *)ft_malloc(sizeof(t_env));
	temp_env->line = ft_strdup(line);
	temp_env->next = NULL;
	add_path_to_list(mini_env, temp_env);
}