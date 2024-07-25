/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:57:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/25 17:04:29 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_export_line(char *env);
void	print_export(t_env **new_export);
void	fill_env_and_export(t_env **new_export, t_env **mini_env, char *args);
void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env);
int 	check_for_append(char **args, t_env **mini_env, t_env **new_export, int i);
void	append_export_and_env(t_env **mini_env, t_env **new_export, char *line, int j);
void	new_append_addition(t_env **new_export, t_env **mini_env, char *line, int pos);

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

int 	check_for_append(char **args, t_env **mini_env, t_env **new_export, int i)
{
	int j;
	char *line;
	// int flag;
	
	j = 0;
	if (ft_strnstr(args[i], "+=", ft_strlen(args[i])) != NULL && args[i][0] != '+')
	{
		if (ft_isalpha(args[i][0]) || args[i][0] == '_')
		{
			while (args[i][j] != '=')
				j++;
			line = ft_substr(args[i], 0, j - 1);
			// printf("That's the line to compare : %s and that's the first : %s\n", line, args[i]);
			append_export_and_env(mini_env, new_export, args[i], j);
			printf("Hello\n");
			free(line);
		}
	}
	else
	{
		// free(line);
		return (1);
	}
	return (0);
}

void append_export_and_env(t_env **mini_env, t_env **new_export, char *line, int j)
{
	t_env *new_env;
	t_env *export;
	char *temp;
	
	temp = ft_substr(line, 0, j - 1);
	new_env = *mini_env;
	while (new_env != NULL)
	{
		if (ft_strnstr(new_env->line, temp, ft_strlen(new_env->line)) != NULL)
		{
			new_env->line = ft_strjoin(new_env->line, line + j + 1);
			break ;
		}
		new_env = new_env->next;
	}
	if (new_env == NULL)
		new_append_addition(new_export, mini_env, line, j);
	export = *new_export;
	while (export != NULL)
	{
		if (ft_strnstr(export->line, temp, ft_strlen(export->line)) != NULL)
		{
			export->line = ft_substr(export->line, 0, ft_strlen(export->line) - 1);
			export->line = ft_strjoin(export->line, line + j + 1);
			export->line = ft_strjoin(export->line, "\"");
			printf("This is the new line : %s and this is the line : %s\n", export->line, line + j + 1);
			break ;
		}
		export = export->next;
	}
}

void new_append_addition(t_env **new_export, t_env **mini_env, char *line, int pos)
{
	char *final1;
	char *final2;
	char *final;


	(void)mini_env;
	(void)new_export;
	final1 = ft_substr(line, 0, pos - 1);
	final2 = ft_substr(line, pos, ft_strlen(line) - pos);
	final = ft_strjoin(final1, final2);
	fill_env_and_export(new_export, mini_env, final);
	free(final1);
	free(final2);
	free(final);
	
}

void	fill_env_and_export(t_env **new_export, t_env **mini_env, char *args)
{
	t_env *new_env;
	t_env *new_export_line;
	
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
	new_export_line->next= NULL;
	add_path_to_list(new_export, new_export_line);
	
}

void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env)
{
	t_env *new_export_line;

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

char	*create_export_line(char *line)
{
	int i;
	char *first_sub_env;
	char *second_sub_env;
	char *first_part;
	char *second_part;

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



