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

/*


ctrl + \ :
in minishell> : it do nothing
in execution if a command was stuck like cat: prirint "quite 3" and kill the current process and keep minishel running

ctrl+C
always ----> new prompt

ctrl+D
in minishell> : it prints exitand then exit the minishel
in exexution if a command was stuck: it exit from the current command only but keeps minishellrunning

*/

#include "../../minishell.h"

void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n"); // newline to ensure the new prompt appears on a fresh line.
		// Display a new prompt
		rl_on_new_line(); // Prepares Readline for a new line of input.
		rl_replace_line("", 0); //Clears the current input line.
		rl_redisplay(); // Refreshes the display to show the new prompt immediately.
	}
}

void	sig_exit(int signal_recived)
{
	if (signal_recived == SIGQUIT)
		write(1, "Quit: 3", 7);
	write(1, "\n", 1);
}

void	setup_signal_init()
{
	struct sigaction sa_int;

	// Handle SIGINT (Ctrl-C)
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask); // This is part of configuring a sigaction structure
									// for setting up a signal handler.
	sa_int.sa_flags = SA_RESTART; // Restart interrupted system calls
	sigaction(SIGINT, &sa_int, NULL);
	// handle SIGQUIT
	signal(SIGQUIT, SIG_IGN); // if the signals was ctrl+/ just call the function SIG_IGN
							// which is used usually to ignor signals
}
void	setup_signal_exe()
{
	struct sigaction sa_int;

	sa_int.sa_handler = sig_exit;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, sig_exit);
}
