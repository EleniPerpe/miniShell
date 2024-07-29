/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:57:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/29 17:09:44 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

// char	*create_export_line(char *env);
// char	*ft_strjoin_export(char const *s1, char const *s2, char c);
// void	print_export(t_env **new_export);
// void	fill_env_and_export(t_env **new_export, t_env **mini_env, char **args, int i);
// void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env);

// void ft_export(t_env **mini_env, char **args, t_env **new_export)
// {
// 	int i;

// 	i = 0;
// 	while (args[i] != NULL)
// 		i++;
// 	if (i == 1)
// 		print_export(new_export);
// 	i = 1;
// 	while (args[i] != NULL)
// 	{
// 		if (ft_strchr(args[i], '=') != NULL && (ft_isalpha(args[i][0])
// 			|| args[i][0] == '_'))
// 				fill_env_and_export(new_export, mini_env, args, i);
// 		else if (ft_isalpha(args[i][0]) || args[i][0] == '_')
// 			fill_only_exp(new_export, args, i, mini_env);
// 		else
// 		{

// 			if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
// 				printf("minishell: %s: '%s': not a valid identifier\n",
// 					args[0], args[i]);
// 		}
// 		i++;
// 	}
// }

// void	fill_env_and_export(t_env **new_export, t_env **mini_env, char **args, int i)
// {
// 	t_env *new_env;
// 	t_env *new_export_line;

// 	new_env = (t_env *)ft_malloc(sizeof(t_env));
// 	new_env->line = ft_strdup(args[i]);
// 	find_if_exists(new_export, args[i], mini_env);
// 	if (!new_env->line)
// 	{
// 		free(new_env);
// 		exit(EXIT_FAILURE);
// 	}
// 	new_env->next = NULL;
// 	add_path_to_list(mini_env, new_env);
// 	new_export_line = (t_env *)ft_malloc(sizeof(t_env));
// 	new_export_line->line = create_export_line(args[i]);
// 	find_if_exists(new_export, new_export_line->line, mini_env);
// 	if (!new_export_line->line)
// 	{
// 		free(new_export_line);
// 		exit(EXIT_FAILURE);
// 	}
// 	new_export_line->next= NULL;
// 	add_path_to_list(new_export, new_export_line);

// }

// void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env)
// {
// 	t_env *new_export_line;

// 	new_export_line = (t_env *)ft_malloc(sizeof(t_env));
// 	new_export_line->line = create_export_line(args[i]);
// 	if (!new_export_line->line)
// 	{
// 		free(new_export_line);
// 		exit(EXIT_FAILURE);
// 	}
// 	find_if_exists(new_export, new_export_line->line, mini_env);
// 	new_export_line->next = NULL;
// 	add_path_to_list(new_export, new_export_line);
// }


// void create_export_path(t_env **mini_env, t_env **new_export)
// {
// 	t_env	*new_env;
// 	int		len;
// 	char	*export_line;
// 	t_env *tmp;

// 	len = 0;
// 	tmp = *mini_env;
// 	while (tmp != NULL)
// 	{
// 		len = ft_strlen(tmp->line) + 13;
// 		export_line = create_export_line(tmp->line);
// 		new_env = (t_env *)ft_malloc(sizeof(t_env));
// 		new_env->line = (char *)ft_malloc(len + 1);
// 		new_env->line = export_line;
// 		new_env->line[len] = '\0';
// 		if (!new_env->line)
// 		{
// 			free(new_env);
// 			exit(EXIT_FAILURE);
// 		}
// 		new_env->next = NULL;
// 		add_path_to_list(new_export, new_env);
// 		tmp = tmp->next;
// 	}
// }

// char	*create_export_line(char *line)
// {
// 	int i;
// 	char *first_sub_env;
// 	char *second_sub_env;
// 	char *first_part;
// 	char *second_part;

// 	i = 0;
// 	if (ft_strchr(line, '=') == NULL)
// 	{
// 		second_part = ft_strjoin("declare -x ", line);
// 		return (second_part);
// 	}
// 	while (line[i] != '=')
// 		i++;
// 	first_sub_env = ft_substr(line, 0, i + 1);
// 	second_sub_env = ft_substr(line, i + 1, ft_strlen(line) - i);
// 	first_part = ft_strjoin("declare -x ", first_sub_env);
// 	second_part = ft_strjoin_export(first_part, second_sub_env, '"');
// 	free(first_sub_env);
// 	free(second_sub_env);
// 	free(first_part);
// 	return (second_part);
// }



#include "../../minishell.h"
char    *create_export_line(char *env);
void    print_export(t_env **new_export);
void    fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env);
void    ft_export(t_env **mini_env, char **args, t_env **new_export)
{
    int i;
    i = 0;
    while (args[i] != NULL)
        i++;
    if (i == 1)
    {
        print_export(new_export);
    }
    i = 1;
    while (args[i] != NULL)
    {
        if (check_for_append(args, mini_env, new_export, i) == 0)
            break ;
        if (ft_strchr(args[i], '=') != NULL && (ft_isalpha(args[i][0])
            || args[i][0] == '_'))
                fill_env_and_export(new_export, mini_env, args[i]);
        else if (ft_isalpha(args[i][0]) || args[i][0] == '_')
            fill_only_exp(new_export, args, i, mini_env);
        else
        {
            if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
                printf("minishell: %s: '%s': not a valid identifier\n",
                    args[0], args[i]);
        }
        i++;
    }
}
void    fill_env_and_export(t_env **new_export, t_env **mini_env, char *args)
{
    t_env   *new_env;
    t_env   *new_export_line;
    new_env = (t_env *)ft_malloc(sizeof(t_env));
    new_env->line = ft_strdup(args);
    find_if_exists(new_export, args, mini_env);
    if (!new_env->line)
    {
        free(new_env);
        exit(EXIT_FAILURE);
    }
    new_env->next = NULL;
    add_path_to_list(mini_env, new_env);
    new_export_line = (t_env *)ft_malloc(sizeof(t_env));
    new_export_line->line = create_export_line(args);
    find_if_exists(new_export, new_export_line->line, mini_env);
    if (!new_export_line->line)
    {
        free(new_export_line);
        exit(EXIT_FAILURE);
    }
    new_export_line->next = NULL;
    add_path_to_list(new_export, new_export_line);
}
void    fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env)
{
    t_env   *new_export_line;
    new_export_line = (t_env *)ft_malloc(sizeof(t_env));
    new_export_line->line = create_export_line(args[i]);
    if (!new_export_line->line)
    {
        free(new_export_line);
        exit(EXIT_FAILURE);
    }
    find_if_exists(new_export, new_export_line->line, mini_env);
    new_export_line->next = NULL;
    add_path_to_list(new_export, new_export_line);
}
void    create_export_path(t_env **mini_env, t_env **new_export)
{
    t_env   *new_env;
    int     len;
    char    *export_line;
    t_env   *tmp;
    len = 0;
    tmp = *mini_env;
    while (tmp != NULL)
    {
        len = ft_strlen(tmp->line) + 13;
        export_line = create_export_line(tmp->line);
        new_env = (t_env *)ft_malloc(sizeof(t_env));
        new_env->line = (char *)ft_malloc(len + 1);
        new_env->line = export_line;
        new_env->line[len] = '\0';
        if (!new_env->line)
        {
            free(new_env);
            exit(EXIT_FAILURE);
        }
        new_env->next = NULL;
        add_path_to_list(new_export, new_env);
        tmp = tmp->next;
    }
}
char    *create_export_line(char *line)
{
    int     i;
    char    *first_sub_env;
    char    *second_sub_env;
    char    *first_part;
    char    *second_part;
    i = 0;
    if (ft_strchr(line, '=') == NULL)
    {
        second_part = ft_strjoin("declare -x ", line);
        return (second_part);
    }
    while (line[i] != '=')
        i++;
    first_sub_env = ft_substr(line, 0, i + 1);
    second_sub_env = ft_substr(line, i + 1, ft_strlen(line) - i);
    first_part = ft_strjoin("declare -x ", first_sub_env);
    second_part = ft_strjoin_export(first_part, second_sub_env, '"');
    free(first_sub_env);
    free(second_sub_env);
    free(first_part);
    return (second_part);
}
