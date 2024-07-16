/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:57:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/16 18:46:15 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void create_export_path(char **env, t_env **new_export);
char *create_export_line(char *env);
char	*ft_strjoin_export(char const *s1, char const *s2, char c);
void print_export(t_env **new_export);

void ft_export(t_env **mini_env, char **args, char **env)
{
	int i;
	t_env *new_env;
	t_env *new_export;

	new_export = NULL;
	create_export_path(env, &new_export);
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		print_export(&new_export);
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL && (ft_isalpha(args[i][0]) || args[i][0] == '_'))
		{	
			new_env = (t_env *)ft_malloc(sizeof(t_env));
			new_env->line = ft_strdup(args[i]);
			if (!new_env->line)
			{
				free(new_env);
				exit(EXIT_FAILURE);
			}
			new_env->next = NULL;
			add_path_to_list(mini_env, new_env);
		}	
		else
		{
			
			if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
				printf("minishell: %s: '%s': not a valid identifier\n", args[0], args[i]);
		}
		i++;
	}
}

void create_export_path(char **env, t_env **new_export)
{
	t_env	*new_env;
	int		i;
	int		len;
	char	*export_line;

	len = 0;
	i = 0;
	while (env[i] != NULL)
	{
		len = ft_strlen(env[i]) + 13;
		export_line = create_export_line(env[i]);
		new_env = (t_env *)ft_malloc(sizeof(t_env));
		new_env->line = (char *)ft_malloc(len + 1);
		new_env->line = export_line;
		new_env->line[len + 1] = '\0';
		if (!new_env->line)
		{
			free(new_env);
			exit(EXIT_FAILURE);
		}
		new_env->next = NULL;
		add_path_to_list(new_export, new_env);
		i++;
	}
}

char *create_export_line(char *env)
{
	int i;
	char *first_sub_env;
	char *second_sub_env;
	char *first_part;
	char *second_part;

	i = 0;
	while (env[i] != '=')
		i++;
	first_sub_env = ft_substr(env, 0, i + 1);
	second_sub_env = ft_substr(env, i + 1, ft_strlen(env) - i);
	first_part = ft_strjoin("declare -x ", first_sub_env);
	second_part = ft_strjoin_export(first_part, second_sub_env, '"');
	free(first_sub_env);
	free(second_sub_env);
	free(first_part);
	return (second_part);
}

char	*ft_strjoin_export(char const *s1, char const *s2, char c)
{
	size_t	s1len;
	size_t	s2len;
	char	*ptr;
	size_t	i;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *)malloc((s1len + s2len + 3) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < s1len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = c;
	i = 0;
	while (i < s2len)
	{
		ptr[s1len + 1 + i] = s2[i];
		i++; 
	}
	ptr[s1len + i + 1] = c;
	ptr[s1len + s2len + 2] = '\0';
	return (ptr);
}

void print_export(t_env **new_export)
{
	t_env *tmp;

	tmp = *new_export;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}