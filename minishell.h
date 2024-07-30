/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:35:18 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/30 17:13:13 by eperperi         ###   ########.fr       */
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

extern pid_t	child_pid;

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
	// int				write_to_pipe;
	// int				read_from_pipe;
	// int				pipe_in;
	// int				pipe_out;
	// pid_t			pro_pid;
	t_line_data		*data_node;
	char			**cmd_args;
	int				i;
	struct s_input	*next;
}	t_input;

// parsing:
char	**ft_split_line(char *input_line,/* t_line_data **line_data,*/ t_env **mini_env, t_input *input_node);
int		redirection_fill(char *line, int i, t_line_data **data);
int		after_redirection_fill(char *line, int i, t_line_data **data);
void	init_nodes_redirctor(t_line_data **data, int type);
void	*ft_malloc(size_t size);
int		command_fill(char *line, int i, t_line_data **data);
void	add_node_to_list(t_line_data **data, t_line_data *new_line_data);
int		quote_token(char *line, int i, t_line_data **line_data);
void	create_path(char **env, t_env **mini_env);
char	*find_path(char *cmd, char **env);
char	**command_merge(t_line_data **data);
char	**merge_free_command(t_line_data **data, int len);
int		heredoc_init(char *line, int i, t_line_data **data);
int		after_redirection_decision(char *line, int i, t_line_data **data);
int		after_redi_len(char *line, int i);
char	*expander_fill(char *line, int i, t_env **mini_env);
void	free_path(t_env *mini_env);
void	init_linked_list(t_input **new_input_node, t_env **mini_env);
int		split_pipes(char *whole_line, t_input **new_input_node);
int		create_input_node(char *whole_line, int i,t_input **new_input_node, int k);
void	add_path_to_list(t_env **mini_env, t_env *new_env);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);

//execution:
void	start_prompt(t_env **mini_env, t_env **new_export, int i);
void	standard_io(t_input *data, int **pipe_fd, int i, int processes_num);
void	reset_io(void);
void	exec_command(char **cmd_args, t_env **mini_env);
void	process_execution(t_input *data, int **pipe_fd,t_env **mini_env, t_env **new_export);
void	close_fds(int **pipe_fd);
void	wait_for_children(int **pro_pid, int processes_num);
void	fork_and_exec(t_input *data, int *process_pid, int **pipe_fd, t_env **mini_env, t_env **new_export);
int		**pipes_init(int processes_num);
int		**pid_init(int processes_num);
void	handle_redirectors(t_input *data);
void	open_infile(t_line_data *data);
void	open_outfile(t_line_data *data, char c);

//builtins
int		check_for_builtins(char **args, t_env **mini_env, t_env **new_export);
int		check_for_builtins(char **args, t_env **mini_env, t_env **new_export);
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
char	*check_expander_and_rest(char *input_line, t_env **mini_env);
void	ft_cd(t_env **mini_env, char **args, t_env **new_export);
void    fill_env_and_export(t_env **new_export, t_env **mini_env, char *args);
int		check_for_append(char **args, t_env **mini_env, t_env **new_export, int i);
void    create_old_pwd(t_env **mini_env, t_env **new_export);
void	ft_exit(char **args);

// utilities
void	ft_free(char **paths_spleted, char *cmd, char *path);
void	free_path(t_env *mini_env);
void	free_all(t_input **input_node, int **pro_pid, int **pipe_fd);
char	**minienv_to_env(t_env **mini_env);

//signals
void	setup_signal_init();
void	setup_signal_exe();

#endif
