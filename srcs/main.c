/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/26 13:01:39 by eperperi         ###   ########.fr       */
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
	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt(env);
	return (0);
}
