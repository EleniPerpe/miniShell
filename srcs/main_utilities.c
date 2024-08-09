/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:23:47 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/07 19:14:09 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_lvl(t_env *current_minienv)
{
	char	*ch_shlvl;
	int		len;
	int		j;
	int		i;

	i = 0;
	j = 0;
	len = ft_strlen(current_minienv->line);
	while (current_minienv->line[i] != '=')
		i++;
	ch_shlvl = (char *)ft_malloc(len - i + 1);
	i++;
	while (i < len)
	{
		ch_shlvl[j] = current_minienv->line[i];
		j++;
		i++;
	}
	ch_shlvl[j] = '\0';
	return (ch_shlvl);
}

void	set_new_lvl(t_env **mini_env, int shlvl)
{
	char	*ch_shlvl;
	t_env	*tmp;

	tmp = *mini_env;
	ch_shlvl = ft_itoa(shlvl);
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->line, "SHLVL", 5))
			break ;
		tmp = tmp->next;
	}
	if (tmp->line != NULL)
		free(tmp->line);
	tmp->line = ft_strjoin("SHLVL=", ch_shlvl);
	free(ch_shlvl);
}

int	handle_oldlvl(char *ch_shlvl, int shlvl)
{
	int	i;

	i = 0;
	while (ch_shlvl[i])
	{
		if (ch_shlvl[i] == '-')
			i++;
		if (!ft_isdigit(ch_shlvl[i]))
		{
			shlvl = 1;
			break ;
		}
		i++;
	}
	if (ch_shlvl[i] == '\0')
	{
		if (shlvl < 0)
			shlvl = 0;
		else
			shlvl++;
	}
	return (shlvl);
}

int	modify_shlvl(t_env **mini_env, char c)
{
	int		shlvl;
	char	*ch_shlvl;
	t_env	*tmp;

	tmp = *mini_env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->line, "SHLVL", 5))
			break ;
		tmp = tmp->next;
	}
	ch_shlvl = get_lvl(tmp);
	shlvl = ft_atoi(ch_shlvl);
	if (c == '+')
		shlvl = handle_oldlvl(ch_shlvl, shlvl);
	else if (c == '-')
		shlvl--;
	free(ch_shlvl);
	set_new_lvl(mini_env, shlvl);
	return (shlvl);
}

void	reset_io(t_inout inout_main)
{
	dup2(inout_main.input, STDIN_FILENO);
	dup2(inout_main.output, STDOUT_FILENO);
}
