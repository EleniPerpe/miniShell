/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:33:43 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/31 03:10:52 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_exit(int signal_recived)
{
	if (signal_recived == SIGQUIT)
		write(1, "^\\Quit: 3", 9);
	if (signal_recived == SIGINT)
		write(1, "^C", 2);
	write(1, "\n", 1);
}

void	setup_signal_init(void)
{
	struct sigaction	sa_int;
	struct termios		new_termios;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	setup_signal_exe(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sig_exit;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, sig_exit);
}
