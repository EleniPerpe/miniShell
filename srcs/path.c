/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:00:29 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/08 17:23:25 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_path_to_list(t_env **mini_env, t_env *new_env);
char *create_final_env(int i, char **env);
int find_expander(char *expander, char **env);
char *final_string(char *expander, char *line, int i, int j);

void create_path(char **env, t_env **mini_env)
{
	t_env *new_env;
	// t_env *tmp;
	int i;
	int j;
//			PRINT THE ENV
// ############################################################################
	// i = 0;
	// while (env[i] != NULL)
	// {
	// 	printf("Env : %s\n", env[i]);
	// 	i++;
	// }
// ############################################################################
	i = 0;
	while (env[i] != NULL)
	{
		new_env = (t_env *)ft_malloc(sizeof(t_env));
		j = ft_strlen(env[i]);
		new_env->line = (char *)ft_malloc(j + 1);
		ft_strlcpy(new_env->line, env[i], j);
		new_env->line[j] = '\0';
		new_env->next = NULL;
		add_path_to_list(mini_env, new_env);
		i++;
	}

	// tmp = *mini_env; // prints the path
	// while (tmp != NULL)
	// {
	// 	printf("Next line : %s\n", tmp->line);
	// 	tmp = tmp->next;
	// }

	// for later

	// while (new_env != NULL)
	// {
	// 	tmp = new_env;
	// 	new_env = new_env->next;
	// 	free(tmp);
	// }
}

void add_path_to_list(t_env **mini_env, t_env *new_env)
{
	t_env *tmp;

	if (*mini_env == NULL)
		*mini_env = new_env;
	else
	{
		tmp = *mini_env;
		while (tmp->next != NULL)   // sometimes it crashes and gives a seg here
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

char	*expander_fill(char *line, int *i, char **env)
{
	char *expander;
	int j;
	int env_position;
	char *final;
	char *env_value;

	j = 0;
	(*i)++;
	while (line[*i + j] != ' ' && line[*i + j] != '\0')
		j++;
	expander = (char *)ft_malloc(j + 1);
	ft_strlcpy(expander, &line[*i], j + 1);
	expander[j] = '\0';
	env_position = find_expander(expander, env);
	env_value = create_final_env(env_position, env);
	final = final_string(env_value, line, *i, j);
	*i = *i + j;
	
	free(expander);
	return (final);
}

char *final_string(char *expander, char *line, int i, int j)
{
	int exp_len;
	int line_len;
	char *final;
	char *before;
	char *after;

	exp_len = ft_strlen(expander);
	line_len = ft_strlen(line) - j;
	
	final = (char *)ft_malloc(exp_len + line_len + 1);
	before = (char *)ft_malloc(i);
	ft_strlcpy(before, line, i);
	before[i - 1] = '\0';
	after = ft_strdup(line + i + j);
	if (!after)
	{
		free(final);
		free(before);
		return (NULL);
	}
	final[0] = '\0';
	ft_strlcat(final, before, exp_len + line_len + 1);
	ft_strlcat(final, expander, exp_len + line_len + 1);
	ft_strlcat(final, after, exp_len + line_len + 1);

	free(before);
	free(after);
	// printf("This is the final : %s\n", final);
	return (final);
	
}

char *create_final_env(int i, char **env)
{
	int j;
	char *res;
	int total_len;

	total_len = ft_strlen(env[i]);
	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	// printf("this is the right one : %s\n", env[i]);
	res = (char *)ft_malloc(total_len - j + 1);
	ft_strlcpy(res, &env[i][j], total_len - j + 1);
	res[total_len - j] = '\0';
	return (res);
}

int find_expander(char *expander, char **env)
{
	int i;
    size_t len = strlen(expander);

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(expander, env[i], len) == 0 && env[i][len] == '=')
		{
			// printf("this is the next one : %s\n", env[i]);
			return (i);
		}
		i++;
	}
	return (0);
}
