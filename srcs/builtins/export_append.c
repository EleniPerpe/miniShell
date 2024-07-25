/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:19:36 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/25 18:49:57 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_export_and_env(t_env **mini_env, t_env **new_export,
			char *line, int j);
void	new_append_addition(t_env **new_export, t_env **mini_env,
			char *line, int pos);
void	append_export(char *temp, char *line, t_env **new_export, int j);

int	check_for_append(char **args, t_env **mini_env, t_env **new_export, int i)
{
	int		j;
	char	*line;

	j = 0;
	if (ft_strnstr(args[i], "+=", ft_strlen(args[i])) != NULL
		&& args[i][0] != '+')
	{
		if (ft_isalpha(args[i][0]) || args[i][0] == '_')
		{
			while (args[i][j] != '=')
				j++;
			line = ft_substr(args[i], 0, j - 1);
			append_export_and_env(mini_env, new_export, args[i], j);
			printf("Hello\n");
			free(line);
		}
	}
	else
	{
		return (1);
	}
	return (0);
}

void	append_export_and_env(t_env **mini_env, t_env **new_export,
		char *line, int j)
{
	t_env	*new_env;
	char	*temp;

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
	append_export(temp, line, new_export, j);
}

void	append_export(char *temp, char *line, t_env **new_export, int j)
{
	t_env	*export;

	export = *new_export;
	while (export != NULL)
	{
		if (ft_strnstr(export->line, temp, ft_strlen(export->line)) != NULL)
		{
			export->line = ft_substr(export->line, 0,
					ft_strlen(export->line) - 1);
			export->line = ft_strjoin(export->line, line + j + 1);
			export->line = ft_strjoin(export->line, "\"");
			break ;
		}
		export = export->next;
	}
}

void	new_append_addition(t_env **new_export, t_env **mini_env,
	char *line, int pos)
{
	char	*final1;
	char	*final2;
	char	*final;

	final1 = ft_substr(line, 0, pos - 1);
	final2 = ft_substr(line, pos, ft_strlen(line) - pos);
	final = ft_strjoin(final1, final2);
	fill_env_and_export(new_export, mini_env, final);
	free(final1);
	free(final2);
	free(final);
}
