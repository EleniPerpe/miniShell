/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 18:36:40 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    change_other_envs(t_env **mini_env, t_env **new_export, char *line);
char    *create_previous_directory(t_env **mini_env);
void	check_for_new_pwd(t_env **mini_env, t_env **new_export,
		int exit_code, char *temp_pwd);
char *join_the_pwd(t_env **mini_env, t_env **new_export, char *temp_pwd);
char *handle_cd_args(t_env **mini_env, char **args, char *old_pwd, int *exit_code);

int    ft_cd(t_env **mini_env, char **args, t_env **new_export)
{
    char    *temp_pwd;
	int		exit_code;
	char 	*old_pwd;

	exit_code = 0;
	temp_pwd = NULL;
	old_pwd = keep_old_pwd(mini_env);
    create_old_pwd(mini_env, new_export);
	temp_pwd = handle_cd_args(mini_env, args, old_pwd, &exit_code);
	if (exit_code == 0 && temp_pwd != NULL)
		check_for_new_pwd(mini_env, new_export, exit_code, temp_pwd);
    return (exit_code);
}

char *handle_cd_args(t_env **mini_env, char **args, char *old_pwd, int *exit_code)
{
	char *temp_pwd;

	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
    {
        temp_pwd = getenv("HOME");
        *exit_code = check_and_change_dir(temp_pwd);
    }
    else if (args[1] != NULL && (ft_strncmp("..", args[1], 2)) == 0)
    {
        temp_pwd = create_previous_directory(mini_env);
        *exit_code = check_and_change_dir(temp_pwd);
    }
	else if (args[1] != NULL && (ft_strncmp("-", args[1], 1)) == 0)
    {
		temp_pwd = ft_substr(old_pwd, 7, ft_strlen(old_pwd) - 7);		
		*exit_code = switch_directories(old_pwd);
    }
	else if (args[1] != NULL && (ft_strncmp(".", args[1], 1)) == 0)
		return (NULL);
    else
    {
        temp_pwd = args[1];
        *exit_code = check_and_change_dir(temp_pwd);
    }
	return (temp_pwd);
}

void	check_for_new_pwd(t_env **mini_env, t_env **new_export,
	int exit_code, char *temp_pwd)
{
	char *new_pwd;
	t_env *temp;
	
	temp = *mini_env;
	if (exit_code == 0 && temp_pwd[0] != '/')
	{
		new_pwd = join_the_pwd(mini_env, new_export, temp_pwd);
	}
	else if (exit_code == 0 && temp_pwd[0] == '/')
	{
    	new_pwd = getcwd(NULL, 0);
    	new_pwd = ft_strjoin("PWD=", temp_pwd);
		change_other_envs(mini_env, new_export, new_pwd);
		free(new_pwd);
	}
}
char *join_the_pwd(t_env **mini_env, t_env **new_export, char *temp_pwd)
{
	t_env *temp;
	char *new_pwd;
	char *temp_str;
	
	temp = *mini_env;
	new_pwd = NULL;
	while (temp != NULL)
	{
		if (ft_strncmp("PWD=", temp->line, 4) == 0)
		{
			temp_str = ft_strjoin(temp->line, "/");
			new_pwd = ft_strjoin(temp_str, temp_pwd);
			free(temp_str);
			change_other_envs(mini_env, new_export, new_pwd);
			free(new_pwd);
			break ;
		}
		temp = temp->next;
	}
	if (new_pwd != NULL)
		return (new_pwd);
	else
		return (NULL);
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
    final = ft_substr(temp->line, 4, len - 4);
    return (final);
}