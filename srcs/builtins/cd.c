/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/23 15:16:22 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_other_envs(t_env **mini_env,t_env **new_export, char *line);
void	replace_nodes(t_env **mini_env, char *line, int i, int bool);

void	ft_cd(t_env **mini_env, char **args, char **env, t_env **new_export)
{
	// char *old_pwd;
	// size_t size = 1024;
	char *home;
	char *new_pwd;

	(void)env;
	if (args[1] == NULL || (args[1][0] == '~' && args[1][0] == '\0'))
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			fprintf(stderr, "Cannot find HOME environment variable\n");
			exit (EXIT_FAILURE);
		}
		printf("Home : %s\n", home);
	}
    if (chdir(home) != 0)
	{
        perror("chdir() error");
        exit (EXIT_FAILURE);
    }
	new_pwd = ft_strjoin("PWD=", home);
	// printf("New home is : %s\n", new_pwd);
	change_other_envs(mini_env, new_export, new_pwd);
	// old_pwd = (char *)ft_malloc(size);
	// if (getcwd(old_pwd, size) != NULL)
	// {
	// 	//fill the old_pwd
	// }
	// else
	// {
    //     perror("getcwd() error");
    // }
	// if (chdir(home) != 0) {
    //     perror("chdir() to HOME failed");
    //     return EXIT_FAILURE;
    // }

	free(new_pwd);
	// free(old_pwd);
}
void	change_other_envs(t_env **mini_env,t_env **new_export, char *line)
{
	int i;
	t_env *current_mini_env;
	t_env *current_new_export;
	
	i = 0;
	current_mini_env = *mini_env;
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
		replace_nodes(new_export, line, i, 2);
}

void replace_nodes(t_env **mini_env, char *line, int i, int bool)
{
	t_env *temp_env;
	
	node_remove(mini_env, line, i);
	temp_env = (t_env *)ft_malloc(sizeof(t_env));
	if (bool == 1)
		temp_env->line = ft_strdup(line);
	else
		temp_env->line = ft_strjoin("declare -x ", line);
	temp_env->next = NULL;
	add_path_to_list(mini_env, temp_env);
}