/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:10:54 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/06 14:37:25 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    append_export_and_env(t_env **mini_env, t_env **new_export,
            char *line, int j);
void    new_append_addition(t_env **new_export, t_env **mini_env,
            char *line, int pos);
void    append_export(char *temp, char *line, t_env **new_export, int j);

int check_for_append(char **args, t_env **mini_env, t_env **new_export, int i)
{
    int     j;
    j = 0;
    if (ft_strnstr(args[i], "+=", ft_strlen(args[i])) != NULL
        && args[i][0] != '+')
    {
        if (ft_isalpha(args[i][0]) || args[i][0] == '_')
        {
            while (args[i][j] != '=')
                j++;
            append_export_and_env(mini_env, new_export, args[i], j);
        }
    }
    else
    {
        return (1);
    }
    return (0);
}

void    append_export_and_env(t_env **mini_env, t_env **new_export,
        char *line, int j)
{
    t_env   *new_env;
    char    *temp;
    char    *cmp_temp;
    temp = ft_substr(line, 0, j - 1);
    cmp_temp = ft_strjoin(temp, "=");
    new_env = *mini_env;
    while (new_env != NULL)
    {
        if (ft_strncmp(new_env->line, cmp_temp, ft_strlen(cmp_temp)) == 0)
        {
            new_env->line = ft_strjoin(new_env->line, line + j + 1);
            break ;
        }
        new_env = new_env->next;
    }
    if (new_env == NULL)
        new_append_addition(new_export, mini_env, line, j);
    else
        append_export(temp, line, new_export, j);
    free(cmp_temp);
}

void    append_export(char *temp, char *line, t_env **new_export, int j)
{
    t_env   *export;
    char    *cmp_temp;
    cmp_temp = ft_strjoin(temp, "=");
    export = *new_export;
    while (export != NULL)
    {
        if (ft_strncmp(export->line + 11, cmp_temp, ft_strlen(cmp_temp)) == 0)
        {
            export->line = ft_substr(export->line, 0,
                    ft_strlen(export->line) - 1);
            export->line = ft_strjoin(export->line, line + j + 1);
            export->line = ft_strjoin(export->line, "\"");
            break ;
        }
        export = export->next;
    }
    free(temp);
    free(line);
    free(cmp_temp);
}

void    new_append_addition(t_env **new_export, t_env **mini_env,
    char *line, int pos)
{
    char    *final1;
    char    *final2;
    char    *final;
    final1 = ft_substr(line, 0, pos - 1);
    final2 = ft_substr(line, pos, ft_strlen(line) - pos);
    final = ft_strjoin(final1, final2);
    fill_env_and_export(new_export, mini_env, final);
    free(final1);
    free(final2);
    free(final);
}

char	*create_export_line(char *line)
{
	int		i;
	char	*first_sub_env;
	char	*second_sub_env;
	char	*first_part;
	char	*second_part;

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
