/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/02 19:08:47 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
void    change_other_envs(t_env **mini_env, t_env **new_export, char *line);
char    *create_previous_directory(t_env **mini_env);
int	    check_and_change_dir(char *dir);
void	check_for_new_pwd(t_env **mini_env, t_env **new_export,
		int exit_code, char *temp_pwd);


int    ft_cd(t_env **mini_env, char **args, t_env **new_export)
{
    char    *temp_pwd;
	int		exit_code;

	exit_code = 0;
    create_old_pwd(mini_env, new_export);
    if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
    {
        temp_pwd = getenv("HOME");
        exit_code = check_and_change_dir(temp_pwd);
    }
    else if (args[1] != NULL && (ft_strncmp("..", args[1], 2)) == 0)
    {
        temp_pwd = create_previous_directory(mini_env);
        exit_code = check_and_change_dir(temp_pwd);
    }
	else if (args[1] != NULL && (ft_strncmp(".", args[1], 1)) == 0)
		return (0);
    else
    {
        temp_pwd = args[1];
        exit_code = check_and_change_dir(args[1]);
    }
	check_for_new_pwd(mini_env, new_export, exit_code, temp_pwd);
    return (exit_code);
}
int    check_and_change_dir(char *dir)
{
    if (dir == NULL)
	{
        fprintf(stderr, "Cannot find environment variable\n");
		return (1);
	}
    if (chdir(dir) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", dir);
		return (1);
	}
	return (0);
}

void	check_for_new_pwd(t_env **mini_env, t_env **new_export,
	int exit_code, char *temp_pwd)
{
	char *new_pwd;

	if (exit_code == 0)
	{
    	new_pwd = getcwd(NULL, 0);
    	new_pwd = ft_strjoin("PWD=", temp_pwd);
    	change_other_envs(mini_env, new_export, new_pwd);
		free(new_pwd);
	}
}
char    *create_previous_directory(t_env **mini_env)
{
    t_env   *temp;
    char    *final;
    int     len;
    char    *rest;
    temp = *mini_env;
	
    while (temp != NULL && ft_strncmp("PWD=", temp->line, 4) != 0)
        temp = temp->next;
    rest = ft_strrchr(temp->line, '/');
    len = ft_strlen(temp->line) - ft_strlen(rest);
    final = (char *)ft_malloc(len + 1);
    final = ft_substr(temp->line, 4, len - 4);
    return (final);
}