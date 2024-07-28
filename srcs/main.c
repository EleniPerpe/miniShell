/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/28 01:45:42 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	open_check()
// {
// 	// via the fd --> open and check wether fd == -1
// 	write(2, "minishell: ", ft_strlen("minishell"));
// 	write(2, 0);
// 	ft_putstr_fd("", )
// 	write (2 ,"minishell: No such file or directory", ft_strlen("minishell: No such file or directory"));
// }

int	main(int argc, char **argv, char **env)
{
	t_env		*mini_env;
	t_env		*new_export;

	mini_env = NULL;
	new_export = NULL;
	create_path(env, &mini_env);
	create_export_path(&mini_env, &new_export);
	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt(env, &mini_env, &new_export);
	return (0);
}
