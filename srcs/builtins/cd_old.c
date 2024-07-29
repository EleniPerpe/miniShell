/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_old.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:09:26 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/29 20:24:33 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
void    check_if_exists(t_env **envs);
void    create_old_pwd(t_env **mini_env, t_env **new_export)
{
    char    *oldpwd;
    size_t  size;
    t_env   *pwd_export;
    t_env   *pwd_env;
    size = 1024;
    check_if_exists(mini_env);
    check_if_exists(new_export);
    oldpwd = (char *)ft_malloc(size);
    if (getcwd(oldpwd, size) != NULL)
    {
        pwd_export = (t_env *)ft_malloc(sizeof(t_env));
        pwd_export->line = ft_strjoin_export("declare -x OLDPWD=", oldpwd, '"');
        pwd_export->next = NULL;
        add_path_to_list(new_export, pwd_export);
        pwd_env = (t_env *)ft_malloc(sizeof(t_env));
        pwd_env->line = ft_strjoin("OLDPWD=", oldpwd);
        pwd_env->next = NULL;
        add_path_to_list(mini_env, pwd_env);
    }
    else
        perror("getcwd() error");
    free(oldpwd);
}
void    check_if_exists(t_env **envs)
{
    t_env   *temp_envs;
    t_env   *next_env;
    char    *temp_export;
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
