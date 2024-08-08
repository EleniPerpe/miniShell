/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:35:18 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/08 17:01:36 by eperperi         ###   ########.fr       */
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
# include <sys/wait.h>
#include <termios.h>
#include <stdbool.h>

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

typedef struct s_inout
{
	int input;
	int output;
}	t_inout;

typedef struct s_envexpo
{
	t_env	**exe_env;
	t_env	**exe_export;
}	t_envexpo;

typedef struct s_commands_list
{
	t_line_data				*commands_node;
	struct s_commands_list	*next;
}	t_commands_list;

typedef struct s_input
{
	char			*part_line;
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
int		quote_token(char *line, int i, t_line_data **line_data, int j);
void	create_path(char **env, t_env **mini_env);
char	*find_path(char *cmd, char **env);
char	**command_merge(t_line_data **data);
char	**merge_free_command(t_line_data **data, int len);
int		heredoc_init(char *line, int i, t_line_data **data);
int		after_redirection_decision(char *line, int i, t_line_data **data);
int		after_redi_len(char *line, int i);
char	*expander_fill(char *line, int i, int j, t_env **mini_env);
void	free_path(t_env *mini_env);
int		init_linked_list(t_input **new_input_node,t_env **mini_env, int processes_num);
int		split_pipes(char *whole_line, t_input **new_input_node);
int		create_input_node(char *whole_line, int i,t_input **new_input_node, int k);
void	add_path_to_list(t_env **mini_env, t_env *new_env);
void	add_inputnode_tolist(t_input **data, t_input *new_line_data);
int		after_heredoc_fill(char *line, int i, t_line_data **data);

//execution:
void	start_prompt(t_env **mini_env, t_env **new_export, t_inout inout_main);
int		standard_io(t_input *data, int **pipe_fd, int i, int processes_num, t_env **mini_env);
void	reset_io(t_inout inout_main);
int		exec_command(char **cmd_args, t_env **mini_env);
int		process_execution(t_input *data, int **pipe_fd,t_env **mini_env, t_env **new_export);
void	close_fds(int **pipe_fd);
void	wait_for_children(int **pro_pid, int processes_num, t_env **mini_env);
int		fork_and_exec(t_input *data, int *process_pid, int **pipe_fd, t_envexpo exe_envexport);
int		**pipes_init(int processes_num);
int		**pid_init(int processes_num);
int		handle_redirectors(t_input *data, t_env **mini_env);
int		open_infile(t_line_data *data, t_env **mini_env);
void	open_outfile(t_line_data *data, char c);

//builtins
int		check_for_builtins(char **args, t_env **mini_env, t_env **new_export);
int		execute_builtins(char **args, t_env **mini_env, t_env **new_export, t_input **free_input);
int		check_if_valid(char **args, t_env **mini_env, t_env **new_export, int i);
int		ft_echo(char **args);
int		ft_env(t_env **mini_env, char **args);
int		ft_pwd(t_env **mini_env);
int		ft_export(t_env **mini_env, char **args, t_env **new_export);
void	create_export_path(t_env **mini_env, t_env **new_export);
void	find_if_exists(t_env **new_export, char *line, t_env **mini_env);
void	print_export(t_env **new_export);
char	*ft_strjoin_export(char const *s1, char const *s2, char c);
int		ft_unset(char **args, t_env **mini_env, t_env **new_export);
void	node_remove(t_env **node_remove, char *line, int i);
char	*check_expander_and_rest(char *input_line, t_env **mini_env, int i);
int    ft_cd(t_env **mini_env, char **args, t_env **new_export, int i);
void	fill_env_and_export(t_env **new_export, t_env **mini_env, char *args);
int		check_for_append(char **args, t_env **mini_env, t_env **new_export, int i);
void	create_old_pwd(t_env **mini_env, t_env **new_export);
int		ft_exit(char **args, t_env **mini_env, t_env **new_export);
void	change_other_envs(t_env **mini_env, t_env **new_export, char *line);
char	*keep_old_pwd(t_env **mini_env);
int		switch_directories(char *old_pwd);
int	    check_and_change_dir(char *dir);
char	*create_export_line(char *line);
void	quotes_after_redireciton(char *line, int j, t_line_data **data);
void	quotes_command(char *line, int j, t_line_data **data);
char	*check_for_available_old(char *old_pwd);
char	*find_full_or_sub(char *args, char *old_pwd);

// utilities
void	ft_free(char **paths_spleted, char *cmd, char *path);
void	free_path(t_env *mini_env);
void	free_all(t_input **input_node, int **pro_pid, int **pipe_fd);
char	**minienv_to_env(t_env **mini_env);
void	add_status(t_env **mini_env);
void	change_status(t_env **mini_env, int status);
int		modify_shlvl(t_env **mini_env, char c);
void	free_env_list(t_env **env);
void	dup_inout(t_inout *inout_main);
int		is_empty(char *str);
void	free_split(char **args);
void	free_nodes(t_input **input_node);

//signals
void	setup_signal_init();
void	setup_signal_exe();

#endif
