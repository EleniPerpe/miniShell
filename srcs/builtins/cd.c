/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:23:28 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/07 16:32:48 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    change_other_envs(t_env **mini_env, t_env **new_export, char *line);
char    *create_previous_directory(t_env **mini_env);
void	check_for_new_pwd(t_env **mini_env, t_env **new_export,
		int exit_code, char *temp_pwd);
char *join_the_pwd(t_env **mini_env, t_env **new_export, char *temp_pwd);
char *handle_cd_args(t_env **mini_env, char *args, char *old_pwd, int *exit_code);
int one_or_more_args(char *args, t_env **mini_env, t_env **new_export, char *old_pwd);
char *find_current_pwd(t_env **mini_env);
void initialize_cd_variables(t_env **mini_env, t_env **new_export, char **old_pwd, int *exit_code);

int    ft_cd(t_env **mini_env, char **args, t_env **new_export, int i)
{
    char    *temp_pwd;
	int		exit_code;
	char 	*old_pwd;
	char	**cd_args;

	initialize_cd_variables(mini_env, new_export, &old_pwd, &exit_code);
	if (args[1] != NULL)
	{
		cd_args = ft_split(args[1], '/');
		while (*cd_args != NULL)
		{
			temp_pwd = handle_cd_args(mini_env, cd_args[i], old_pwd, &exit_code);
			if (exit_code == 0 && temp_pwd != NULL)
				check_for_new_pwd(mini_env, new_export, exit_code, temp_pwd);
			cd_args++;
		}
	}
	else
	{
		temp_pwd = handle_cd_args(mini_env, args[1], old_pwd, &exit_code);
		if (exit_code == 0 && temp_pwd != NULL)
			check_for_new_pwd(mini_env, new_export, exit_code, temp_pwd);
		return (free(old_pwd), exit_code);
	}
    return (free(old_pwd), free(temp_pwd), exit_code);
}

void initialize_cd_variables(t_env **mini_env, t_env **new_export, char **old_pwd, int *exit_code)
{
    *exit_code = 0;
    *old_pwd = keep_old_pwd(mini_env);
    create_old_pwd(mini_env, new_export);
}

char *handle_cd_args(t_env **mini_env, char *args, char *old_pwd, int *exit_code)
{
	char *temp_pwd;

	if (args == NULL || (args[0] == '~' && args[1] == '\0'))
    {
        temp_pwd = ft_strdup(getenv("HOME"));
        *exit_code = check_and_change_dir(temp_pwd);
    }
    else if (args != NULL && (ft_strncmp("..", args, 2)) == 0)
    {
        temp_pwd = create_previous_directory(mini_env);
        *exit_code = check_and_change_dir(temp_pwd);
    }
	else if (args != NULL && (ft_strncmp("-", args, 1)) == 0)
    {
		temp_pwd = check_for_available_old(old_pwd);
		*exit_code = switch_directories(old_pwd);
    }
	else if (args != NULL && (ft_strncmp(".", args, 1)) == 0)
		temp_pwd = find_current_pwd(mini_env);
    else
    {
        temp_pwd = args;
        *exit_code = check_and_change_dir(temp_pwd);
    }
	return (temp_pwd);
}

char *find_current_pwd(t_env **mini_env)
{
	t_env *temp;
	char *res;

	temp = *mini_env;
	res = NULL;
	while (temp != NULL)
	{
		if (ft_strncmp("PWD", temp->line, 3) == 0)
			res = ft_strdup(temp->line + 4);
		temp = temp->next;
	}
	return (res);
}

void	check_for_new_pwd(t_env **mini_env, t_env **new_export,
	int exit_code, char *temp_pwd)
{
	char *new_pwd;
	
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
