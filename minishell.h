/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:35:18 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/04 17:16:23 by eperperi         ###   ########.fr       */
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
# include <unistd.h>
# include <errno.h>

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
	char				*expander; // "$PATH";
	int					type; //redir:  2 3 4 .... command = 1 expander =
	struct s_line_data	*next;
}	t_line_data;

typedef struct s_env
{
	char 			*line;
	struct s_env	*next;
}	t_env;

void	start_prompt(char **env);
void	ft_split_line(char *input_line, t_line_data **line_data, char **env);
int		redirection_fill(char *line, int i, t_line_data **data, char **env);
int		after_redirection_fill(char *line, int i, t_line_data **data);
void	init_nodes_redirctor(t_line_data **data, int type);
void	*ft_malloc(size_t size);
int		command_fill(char *line, int i, t_line_data **data);
void	add_node_to_list(t_line_data **data, t_line_data *new_line_data);
int		ft_split_pipe(char *line, t_line_data **line_data, char p, int i, char **env);
int		quote_token(char *line, int i, t_line_data **line_data, char **env);
void	create_path(char **env, t_env **mini_env);
void	standard_IO(t_line_data *line_data);
void	reset_IO(void);
char	*find_path(char *cmd, char **env);
void	exec_command(t_line_data *line_data, char **env);
void	ft_free(char **paths_spleted, char *cmd, char *path);
void	command_merage(t_line_data **data);
void	merage_free_command(t_line_data **data, int len);
int	expander_fill(char *line, int i, t_line_data **data, char **env);

#endif

