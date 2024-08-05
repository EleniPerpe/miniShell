/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_back.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:11:31 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/05 18:09:39 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *keep_old_pwd(t_env **mini_env)
{
	t_env *temp;
	char *temp_old_pwd;
	
	temp = *mini_env;
	while (temp != NULL)
	{
		if (ft_strncmp("OLDPWD", temp->line, 6) == 0)
		{	
			temp_old_pwd = ft_substr(temp->line, 0, ft_strlen(temp->line));
			return (temp_old_pwd);
		}
		temp = temp->next;
	}
	return (NULL);
}

int switch_directories(char *old_pwd)
{
	char *temp_pwd;
	int exit_code;
	
	temp_pwd = NULL;
	if (old_pwd == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	else
		temp_pwd = ft_substr(old_pwd, 3, ft_strlen(old_pwd) - 3);
	if (temp_pwd != NULL)
	{	
    	exit_code = check_and_change_dir(temp_pwd + 4);
		return (exit_code);
	}
	else
		return (0);
}

int    check_and_change_dir(char *dir)
{
	printf("dir : %s\n", dir);
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