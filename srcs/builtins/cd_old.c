/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_old.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:09:26 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/05 13:33:52 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    check_if_exists(t_env **envs);
void    replace_nodes(t_env **mini_env, char *line, int i);

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
void    change_other_envs(t_env **mini_env, t_env **new_export, char *line)
{
    int     i;
    t_env   *curr_minienv;
    t_env   *curexport;
    char    *temp_export;
    i = 0;
    curr_minienv = *mini_env;
    while (line[i] != '=' && line[i] != '\0')
        i++;
    while (curr_minienv != NULL && ft_strncmp(curr_minienv->line, line, i) != 0)
        curr_minienv = curr_minienv->next;
    if (curr_minienv != NULL)
        replace_nodes(mini_env, line, i);
    curexport = *new_export;
    while (curexport != NULL && ft_strncmp(curexport->line + 11, line, i) != 0)
        curexport = curexport->next;
    if (curexport != NULL)
    {
        temp_export = ft_strjoin_export("declare -x PWD=", line + 4, '"');
        replace_nodes(new_export, temp_export, i + 11);
    }
}
void    replace_nodes(t_env **mini_env, char *line, int i)
{
    t_env   *temp_env;
    node_remove(mini_env, line, i);
    temp_env = (t_env *)ft_malloc(sizeof(t_env));
    temp_env->line = ft_strdup(line);
    temp_env->next = NULL;
    add_path_to_list(mini_env, temp_env);
}
