/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:35:18 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/29 00:45:45 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include "Get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// type:
// command = 0;
// expander = 1;
//	<< = 2;
//	>> = 3;
//  > = 4;
//  < = 5;
//  | = 6;
// after_redirector = 7;

typedef struct s_line_data
{
	char				*redirctor; // ">>" , "<<" , "<" , ">" , "|";
	char				*after_redirctor; // "file";
	char				**command; // "LS" , "-l";
//	char				*expander; // "$PATH";
	int					type; //redir:  2 3 4 .... command = 1 expander =
	struct s_line_data	*next;
}	t_line_data;

void	start_prompt(void);
void	ft_split_line(char *input_line, t_line_data **line_data);
char	*ft_split_redirctor(char *input_line, t_line_data **line_data);
char	*split_after_redirctor(char *input_line);

#endif

