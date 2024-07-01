/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:56:18 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/01 15:13:02 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_split_pipe(char *line, t_line_data **line_data, char p, int i, char **env)
// {
// 	int pfd[2];
// 	pid_t pid;
// 	int status;
// 	// t_line_data	*new_line_data;

// 	if (pipe(pfd) == -1)
// 		handle_error("pipe", EXIT_FAILURE);
// 	pid = fork();
// 	if (pid == -1)
// 		handle_error("fork", EXIT_FAILURE);
// 	if (pid == 0)
// 		child1((*line_data)->command, pfd, env);
// 	child2((*line_data)->command, pfd, env);
// 	close(pfd[0]);
// 	close(pfd[1]);
// 	waitpid(pid, &status, 0);
// 	;
// }