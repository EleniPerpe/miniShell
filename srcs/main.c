/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/30 17:11:29 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env		*mini_env;
	t_env		*new_export;
	int			i;

	i = 0;
	mini_env = NULL;
	new_export = NULL;
	setup_signal_init();
	create_path(env, &mini_env);
	create_export_path(&mini_env, &new_export);
	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt(&mini_env, &new_export, i);
	return (0);
}
