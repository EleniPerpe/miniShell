/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:09:57 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/12 17:31:41 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_final_env(int i, char **env);
int		find_expander(char *expander, char **env);
char	*final_string(char *expander, char *line, int i, int j);

char	*expander_fill(char *line, int *i, char **env)
{
	char	*expander;
	int		j;
	int		env_position;
	char	*final;
	char	*env_value;

	j = 0;
	(*i)++;
	while ((line[*i + j] != ' ' && line[*i + j] != '\'' && line[*i + j] != '"')
		&& line[*i + j] != '\0')
		j++;
	expander = (char *)ft_malloc(j + 1);
	ft_strlcpy(expander, &line[*i], j + 1);
	expander[j] = '\0';
	if (*i > 1)
	{
		if (line[*i - 2] == '\'')
		{
			free(expander);
			return (line);
		}
	}
	env_position = find_expander(expander, env);
	env_value = create_final_env(env_position, env);
	final = final_string(env_value, line, *i, j);
	*i = *i + j;
	free(expander);
	return (final);
}

char	*final_string(char *expander, char *line, int i, int j)
{
	int		exp_len;
	int		line_len;
	char	*final;
	char	*before;
	char	*after;

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
	return (free(before), free(after), final);
}

char	*create_final_env(int i, char **env)
{
	int		j;
	char	*res;
	int		total_len;

	total_len = ft_strlen(env[i]);
	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	res = (char *)ft_malloc(total_len - j + 1);
	ft_strlcpy(res, &env[i][j], total_len - j + 1);
	res[total_len - j] = '\0';
	return (res);
}

int	find_expander(char *expander, char **env)
{
	int		i;
	size_t	len;

	len = strlen(expander);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(expander, env[i], len) == 0 && env[i][len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (0);
}
