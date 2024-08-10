/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:57:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:06 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_env **new_export);
void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env);
int		check_and_fill(char **args, t_env **mini_env,
			t_env **new_export, int flag);

int	ft_export(t_env **mini_env, char **args, t_env **new_export)
{
	int	i;
	int	exit_code;
	int	flag;

	flag = 0;
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		print_export(new_export);
	exit_code = check_and_fill(args, mini_env, new_export, flag);
	return (exit_code);
}

int	check_and_fill(char **args, t_env **mini_env, t_env **new_export, int flag)
{
	int	i;

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
			{
				printf("minishell: %s: '%s': not a valid identifier\n",
					args[0], args[i]);
				flag = 1;
			}
		}
		i++;
	}
	return (flag);
}

void	fill_env_and_export(t_env **new_export, t_env **mini_env, char *args)
{
	t_env	*new_env;
	t_env	*new_export_line;

	find_if_exists(new_export, args, mini_env);
	new_env = (t_env *)ft_malloc(sizeof(t_env));
	new_env->line = ft_strdup(args);
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

void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env)
{
	t_env	*new_export_line;

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

// int	ft_export(t_env **mini_env, char **args, t_env **new_export)
// {
// 	int	i;
// 	int exit_code;
// 	int flag;

// 	i = 0;
// 	flag = 0;
// 	while (args[i] != NULL)
// 		i++;
// 	if (i == 1)
// 		print_export(new_export);
// 	exit_code = check_and_fill(args, mini_env, new_export, flag);
// 	return (exit_code);
// }

// int		check_and_fill(char **args, t_env **mini_env, t_env **new_export, int flag)
// {
// 	int	i;

// 	i = 1;
// 	while (args[i] != NULL)
// 	{
// 		if (check_for_append(args, mini_env, new_export, i) == 0)
// 			break ;
// 		if (ft_strchr(args[i], '=') != NULL && (ft_isalpha(args[i][0])
// 			|| args[i][0] == '_'))
// 			fill_env_and_export(new_export, mini_env, args[i]);
// 		else if (ft_isalpha(args[i][0]) || args[i][0] == '_')
// 			fill_only_exp(new_export, args, i, mini_env);
// 		else
// 		{
// 			if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
// 			{
// 				printf("minishell: %s: `%s': not a valid identifier\n",
// 					args[0], args[i]);
// 				flag = 1;
// 			}
// 		}
// 		i++;
// 	}
// 	return (return_flag(flag));
// 	// if (flag == 1)
// 	// 	return (1);
// 	// else
// 	// return (0);
// }

// int return_flag(int flag)
// {
// 	if (flag == 1)
// 		return (1);
// 	else
// 	return (0);
// }

// void	fill_env_and_export(t_env **new_export, t_env **mini_env, char *args)
// {
// 	t_env	*new_env;
// 	t_env	*new_export_line;

// 	new_env = (t_env *)ft_malloc(sizeof(t_env));
// 	new_env->line = ft_strdup(args);
// 	if (!new_env->line)
// 	{
// 		free(new_env);
// 		exit(EXIT_FAILURE);
// 	}
// 	find_if_exists(mini_env, args, mini_env);
// 	new_env->next = NULL;
// 	add_path_to_list(mini_env, new_env);
// 	new_export_line = (t_env *)ft_malloc(sizeof(t_env));
// 	new_export_line->line = create_export_line(args);
// 	find_if_exists(new_export, new_export_line->line, mini_env);
// 	if (!new_export_line->line)
// 	{
// 		free(new_export_line);
// 		exit(EXIT_FAILURE);
// 	}
// 	new_export_line->next = NULL;
// 	add_path_to_list(new_export, new_export_line);
// }

// void	fill_only_exp(t_env **new_export, char **args, int i, t_env **mini_env)
// {
// 	t_env	*new_export_line;

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

