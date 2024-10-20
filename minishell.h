/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:31 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 20:48:23 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define BUILTIN 9
# define HEREDOC 10
# define APPEND 11
# define INPUT 12
# define OUTPUT 13
# define C_PROCESS 101
# define M_PROCESS 100
# define HEREDOC_PROECESS 102
# define BUFFER_SIZE 42

int						g_globals_exit;

typedef struct s_cmd
{
	// quote
	int					idx;
	int					dquote_count;
	int					squote_count;
	bool				dquote;
	bool				squote;

	// parse
	char				*line;
	char				**ncmd;
	char				***command;
	int					pipe_count;
	char				*cleaned;
	char				**sep_path;

	int					status;
	int					**fd;
	char				**envp;

	struct s_env		*env;
	struct s_env		*exp;
	struct s_redirect	*redirect;
	struct s_executor	*executor;
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_redirect
{
	int type; // 10: heredoc, 11: append, 12: input, 13: output
	char				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_files
{
	int					fd_heredoc[2];
	int					error;
	int					fd_input;
	int					fd_output;
	char				*input;
	char				*output;
	char				*heredoc;
}						t_files;

typedef struct s_executor
{
	char				**argv;
	pid_t				pid;
	t_files				*files;
	struct s_executor	*next;
}						t_executor;

void	print_cmd(t_cmd *str); // silinecek!!

// env
t_env					*create_env_node(char *key, char *value);
void					add_env_node(t_env **env_list, char *key, char *value);
char					*get_env(t_cmd *cmd, char *key, char *dollar_value);
void					print_env_list(t_cmd *cmd, t_env *env_list);
void					print_export_list(t_cmd *cmd, t_env *env_list);

// utils
char					*get_next_line(int fd);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strndup(const char *s, size_t n);
size_t					ft_strnlen(const char *src, size_t i);
int						ft_isspace(char c);
char					**ft_split2(char const *s, char c);
void					ft_split_space(t_cmd *str);
int						ft_toggle_quote(char c, int in_quote);
void					handle_quotes(char temp, int *squotes, int *dquotes);

// builtins
int						special_char(char c);
int						builtin_check(t_cmd *cmd);
void					builtin_handle(t_cmd *cmd, t_executor *executor);
void					ft_exit(t_cmd *cmd);
void					ft_pwd(t_cmd *str);
void					ft_echo(t_cmd *cmd, t_executor *executor);
void					ft_cd(t_cmd *cmd);
void					ft_unset(t_env **env_list, char *key);
void					ft_export(t_cmd *cmd, char **key_value,
							char *trimmed_quote);
void					parse_env(t_cmd *cmd, char **envp, t_env **env_list);

// parse
char					*remove_quotes(t_cmd *cmd, char *str);
char					**env_to_array(t_env *env_list);
void					sep_path(t_cmd *cmd);
t_files					*init_redirect(t_cmd *cmd, t_files *files);
int						ft_parser(t_cmd *str);
int						wait_for_input(t_cmd *cmd);
int						quote_check(t_cmd *str, char *line);
int						pipe_check(char *line);
int						wait_for_input(t_cmd *cmd);
int						dollar_handle(t_cmd *str);

// redirect
int						redirect_check(char *line);
void					redirect_handle(t_cmd *str);
t_files					*files_init_append(t_files *node, char *arg);
t_files					*files_init_output(t_files *node, char *arg);
t_files					*files_init_input(t_files *node, char *arg);

// executor
void					ft_executor(t_cmd *cmd, int i);
void					close_pipe(t_cmd *cmd, int check);
void					duplication(t_cmd *cmd, t_executor *executor, int check,
							int i);
void					add_exec_node(t_cmd *cmd, t_executor **exec_list);
t_files					*files_init(t_files *node);
char					*get_path(t_cmd *cmd, t_executor *exec);
void					wait_child_process(t_cmd *cmd, int check);
char					**ft_find_cmd(char **arg, int len);
int						ft_cmd_len(char **arg);
char					**fill_argv(char **arg);

// free
void					ft_free_command(char ***str);
void					free_double(char **str);
void					free_env_list(t_env *env_list);
void					ft_full_free(t_cmd *str);
void					free_dollar(char *dollar_before, char *dollar_after,
							char *dollar_value, char *line);
void					free_fd(t_cmd *cmd);
void					free_redirect(t_redirect **redirect);
void					free_executor(t_executor **executor);

// error
int						error_message(char *str);
void					executer_error(char **cmd, char *s, int exit_code);

#endif
