/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:23:47 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/02 18:14:09 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_lvl(t_env *current_minienv)
{
	char	*ch_shlvl;
	int	len;
	int	j;
	int	i;

	i = 0;
	j = 0;
	len = ft_strlen(current_minienv->line);
	while (current_minienv->line[i] != '=')
		i++;
	ch_shlvl = (char *)ft_malloc(len - i + 1);
	i++;
	while(i < len)
	{
		ch_shlvl[j] = current_minienv->line[i];
		j++;
		i++;
	}
	ch_shlvl[j] = '\0';
	return (ch_shlvl);
}

void	set_new_lvl(t_env **mini_env,int shlvl)
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
	tmp->line = (char *)ft_malloc(ft_strlen("SHLVL=") + ft_strlen(ch_shlvl));
	tmp->line = ft_strjoin("SHLVL=", ch_shlvl);
	free(ch_shlvl);
}


void	modify_shlvl(t_env **mini_env, char c)
{
	int		shlvl;
	char	*ch_shlvl;
	t_env	*tmp;
	(void)mini_env;
	tmp = NULL;

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
		shlvl++;
	else if (c == '-')
		shlvl--;
	set_new_lvl(mini_env, shlvl);
}
void	dup_inout(t_inout *inout_main)
{
	inout_main->input = dup(STDIN_FILENO);
	inout_main->output = dup(STDOUT_FILENO);
}
void	reset_io(t_inout inout_main)
{
	dup2(inout_main.input, STDIN_FILENO);
	dup2(inout_main.output, STDOUT_FILENO);
}
