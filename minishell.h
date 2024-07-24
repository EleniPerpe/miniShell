/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:35:18 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/24 16:57:07 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

extern pid_t child_pid;

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
	char				*redirctor;
	char				*after_redirctor;
	char				*command;
	int					type;
	struct s_line_data	*next;
}	t_line_data;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_commands_list
{
	t_line_data				*commands_node;
	struct s_commands_list	*next;
}	t_commands_list;

typedef struct s_input
{
	char			*part_line; // string of characters between two pipes or the end of the line
	int				write_to_pipe; // if there is a pipe set it as STDOUT to this node
	int				read_from_pipe;//if there is a pipe set it as STDIN to the next node
	int				pipe_in; // to get pip_fd[1] which allow us to write data into the pipe
	int				pipe_out;//  to get pip_fd[0] which allow us to read data from the pipe
	t_line_data		*data_node;	// first node of our old linked list
	struct s_input	*next;
}	t_input;

void	start_prompt(char **env);
char	**ft_split_line(char *input_line, t_line_data **line_data, char **env, t_input **input_node);
int		redirection_fill(char *line, int i, t_line_data **data);
int		after_redirection_fill(char *line, int i, t_line_data **data);
void	init_nodes_redirctor(t_line_data **data, int type);
void	*ft_malloc(size_t size);
int		command_fill(char *line, int i, t_line_data **data);
void	add_node_to_list(t_line_data **data, t_line_data *new_line_data);
// int		ft_split_pipe(char *line, t_line_data **line_data, char p, int i, char **env);
int		quote_token(char *line, int i, t_line_data **line_data);
void	create_path(char **env, t_env **mini_env);
void	standard_io(t_input **data);
void	reset_io(void);
char	*find_path(char *cmd, char **env);
void	exec_command(char **cmd_args, char **env);
void	ft_free(char **paths_spleted, char *cmd, char *path);
char	**command_merge(t_line_data **data);
char	**merge_free_command(t_line_data **data, int len);
void	process_execution(t_input **data, char **cmd_args, char **env);
int		heredoc_init(char *line, int i, t_line_data **data);
int		after_redirection_decision(char *line, int i, t_line_data **data);
int		after_redi_len(char *line, int i);
char	*expander_fill(char *line, int i, char **env);
void	free_path(t_env *mini_env);
void	start_real_work(t_input **new_input_node, t_env **mini_env, char **env, t_env **new_export);
void	split_pipes(char *whole_line, t_input **new_input_node);
int		create_input_node(char *whole_line, int i,t_input **new_input_node);
t_input	*get_last_node(t_input **node);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);
void	add_path_to_list(t_env **mini_env, t_env *new_env);
int		check_for_builtins(char **args, t_env **mini_env, t_env **new_export, char **env);
void	ft_echo(char **args);
void	ft_env(t_env **mini_env, char **args);
void	ft_pwd(t_env **mini_env, char **args);
void	ft_export(t_env **mini_env, char **args, t_env **new_export);
void	create_export_path(t_env **mini_env, t_env **new_export);
void	find_if_exists(t_env **new_export, char *line, t_env **mini_env);
void	print_export(t_env **new_export);
char	*ft_strjoin_export(char const *s1, char const *s2, char c);
void	ft_unset(char **args, t_env **mini_env, t_env **new_export);
void	node_remove(t_env **node_remove, char *line, int i);
char	*check_expander_and_rest(char *input_line, char **env);
void	ft_cd(t_env **mini_env, char **args, t_env **new_export);
//void	free_list(t_line_data *line_data);

#endif
