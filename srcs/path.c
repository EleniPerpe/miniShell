/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:00:29 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/08 05:59:06 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_path_to_list(t_env **mini_env, t_env *new_env);
char *create_final_env(int i, char **env);
int find_expander(char *expander, char **env);

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

int	expander_fill(char *line, int i, t_line_data **data, char **env)
{
	t_line_data *new_line_data;
	char *expander;
	int j;
	int env_position;
	char *final_env;

	printf("this is the i in the quotes : %d\n", i);
	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	j = 0;
	i++;
	// I add some extra conditions in this while
	while ((line[i + j] != ' ' && line[i + j] != '\0') &&
		(line[i + j] != '<' && line[i + j] != '>') && (line[i + j] != '|'))
		j++;
	expander = (char *)ft_malloc(j + 1);
	ft_strlcpy(expander, &line[i], j + 1);
	expander[j] = '\0';
	env_position = find_expander(expander, env);
	i = i + j;
	if (i != 0)
	{
		while (line[i] != ' ' && i >= 0)
		{
			if (line[i] == '>' || line[i] == '<')
			{
				new_line_data->type = 7;
				break ;
			}
			else
			{
				new_line_data->type = 1;
				break ;
			}
			i--;
		}
	}
	else
		new_line_data->type = 1;
	// new_line_data->type = 1;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	new_line_data->after_redirctor = NULL;
	new_line_data->next = NULL;
	final_env = create_final_env(env_position, env);
	new_line_data->expander = (char *)ft_malloc(ft_strlen(final_env) + 1);
	ft_strlcpy(new_line_data->expander, final_env, ft_strlen(final_env) + 1);
	new_line_data->expander[ft_strlen(final_env) + 1] = '\0';
	add_node_to_list(data, new_line_data);
	// printf("Expander is : %s", new_line_data->expander);
	free(expander);
	printf ("edw einai to i : %d\n", i);
	return (i);
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
	// printf("that's the total size : %d\n", total_len - j + 1);
	// printf("That's the starting character : %c\n", env[i][j]);
	ft_strlcpy(res, &env[i][j], total_len - j + 1);
	res[total_len - j] = '\0';
	// printf("the final string is : %s\n", res);
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
