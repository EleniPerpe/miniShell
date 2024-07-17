/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:57:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/17 11:56:41 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// I have to add only in export even if it's empty variable
// I have to check if the variable exists already so to modify it 
// instead of adding a new one

char	*create_export_line(char *env, t_env **new_export);
char	*ft_strjoin_export(char const *s1, char const *s2, char c);
void	print_export(t_env **new_export);
void	fill_env_and_export(t_env **new_export, t_env **mini_env, char **args, int i);
void	fill_only_export(t_env **new_export, char **args, int i);
void	find_if_exists(t_env **new_export, char *line);


void ft_export(t_env **mini_env, char **args, t_env **new_export)
{
	int i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		print_export(new_export);
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL && (ft_isalpha(args[i][0])
			|| args[i][0] == '_'))
			fill_env_and_export(new_export, mini_env, args, i);
		else if (ft_isalpha(args[i][0]) || args[i][0] == '_')
			fill_only_export(new_export, args, i);
		else
		{
			
			if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
				printf("minishell: %s: '%s': not a valid identifier\n",
					args[0], args[i]);
		}
		i++;
	}
}

void	fill_env_and_export(t_env **new_export, t_env **mini_env, char **args, int i)
{
	t_env *new_env;
	t_env *new_export_line;
	
	new_env = (t_env *)ft_malloc(sizeof(t_env));
	new_env->line = ft_strdup(args[i]);
	if (!new_env->line)
	{
		free(new_env);
		exit(EXIT_FAILURE);
	}
	new_env->next = NULL;
	add_path_to_list(mini_env, new_env);
	new_export_line = (t_env *)ft_malloc(sizeof(t_env));
	new_export_line->line = create_export_line(args[i], new_export);
	if (!new_export_line->line)
	{
		free(new_export_line);
		exit(EXIT_FAILURE);
	}
	new_export_line->next= NULL;
	add_path_to_list(new_export, new_export_line);
	
}

void	fill_only_export(t_env **new_export, char **args, int i)
{
	t_env *new_export_line;

	new_export_line = (t_env *)ft_malloc(sizeof(t_env));
	new_export_line->line = create_export_line(args[i], new_export);
	if (!new_export_line->line)
	{
		free(new_export_line);
		exit(EXIT_FAILURE);
	}
	new_export_line->next = NULL;
	add_path_to_list(new_export, new_export_line);
}


void create_export_path(t_env **mini_env, t_env **new_export)
{
	t_env	*new_env;
	int		len;
	char	*export_line;
	t_env *tmp;

	len = 0;
	tmp = *mini_env;
	while (tmp != NULL)
	{
		len = ft_strlen(tmp->line) + 13;
		export_line = create_export_line(tmp->line, new_export);
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

char	*create_export_line(char *line, t_env **new_export)
{
	int i;
	char *first_sub_env;
	char *second_sub_env;
	char *first_part;
	char *second_part;

	i = 0;
	(void)new_export;
	// find_if_exists(new_export, line);
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

// void	find_if_exists(t_env **new_export, char *line)
// {
// 	t_env *tmp;
// 	t_env *prev;
// 	int i;
	
// 	i = 0;
// 	while (line[i] != '=')
// 		i++;
	
// 	tmp = *new_export;
// 	prev = NULL;
// 	while (tmp != NULL)
// 	{
// 		if (ft_strncmp(line, tmp->line, i) == 0)
// 		{
// 			if (prev == NULL)
// 				*new_export = tmp->next;
// 			else
// 				prev->next = tmp->next;
// 		free(tmp->line);
// 		free(tmp);
// 		if (prev == NULL)
//                 tmp = *new_export;
//             else
//                 tmp = prev->next;
// 		}
// 		else
// 		{
// 			prev = tmp;
// 			tmp = tmp->next;
// 		}
// 	}
// }


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
	return (ptr[s1len + s2len + 2] = '\0', ptr);
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