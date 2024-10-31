/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:31 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/31 18:59:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define HEREDOC 10
# define APPEND 11
# define INPUT 12
# define OUTPUT 13
# define C_PROCESS 101
# define M_PROCESS 100
# define HEREDOC_PROECESS 102
# define BUFFER_SIZE 42


enum e_signal_mode {
    NOTHING,
    MAIN_MODE,
    HEREDOC_MODE,
    CHILD_MODE
};

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
	char				*new_line;
	char				**ncmd;
	char				***command;
	char				*cleaned;
	char				**sep_path;
	int					pipe_count;

	int					status;
	int					**fd;
	char				**envp;

	struct s_env		*env;
	struct s_env		*exp;
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
	int					fd_input;
	int					fd_output;
	int					error;
	char				*input;
	char				*output;
	char				*heredoc;
}						t_files;

typedef struct s_executor
{
	char				**argv;
	pid_t				pid;
	t_files				*files;
	t_redirect			*redirect;
	struct s_executor	*next;
}						t_executor;

void	print_cmd(t_cmd *str); // silinecek!!

// env
t_env					*create_env_node(char *key, char *value);
void					add_env_node(t_env **env_list, char *key, char *value);
char					*get_env(t_cmd *cmd, char *key, char *dollar_value);
void					print_env_list(t_cmd *cmd, t_env *env_list,
							t_executor *executor);

// utils
char					*get_next_line(int fd);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, int n);
char					*ft_strndup(const char *s, size_t n);
size_t					ft_strnlen(const char *src, size_t i);
int						ft_isspace(char c);
char					**ft_split2(char const *s, char c);
void					ft_split_space(t_cmd *str);
int						ft_toggle_quote(char c, int in_quote);
void					handle_quotes(char temp, int *squotes, int *dquotes);
void    signal_init(enum e_signal_mode mode);

// builtins
int						special_char(char c);
int						builtin_check(char *cmd);
void					builtin_handle(t_cmd *cmd, t_executor *executor);
void					ft_exit(t_cmd *cmd);
void					ft_pwd(t_cmd *str);
void					ft_echo(t_cmd *cmd, t_executor *executor);
void					ft_cd(t_cmd *cmd);
void					ft_unset(t_env **env_list, char **keys);
void	ft_export(t_cmd *cmd);
void	only_export(t_cmd *cmd, char *cleaned);
void	export_both_list(t_cmd *cmd, char *cleaned, char *delimiter);
void					parse_env(t_cmd *cmd, char **envp, t_env **env_list);

// parse
char					*remove_quotes(t_cmd *cmd, char *str);
char					**env_to_array(t_env *env_list, t_env *temp, int i,
							int count);
void					sep_path(t_cmd *cmd);
t_files					*init_redirect(t_cmd *cmd, t_files *files,
							t_executor *executor);
int						ft_parser(t_cmd *str);
int						wait_for_input(t_cmd *cmd);
int						quote_check(t_cmd *str, char *line);
int						pipe_check(char *line);
int						wait_for_input(t_cmd *cmd);
int						dollar_handle(t_cmd *str);

// redirect
int						redirect_check(t_cmd *cmd, char *line);
void					redirect_handle(t_cmd *cmd, t_executor *temp, int *i);
t_files					*files_init_append(t_files *files, char *filename);
t_files					*files_init_output(t_files *files, char *filename);
t_files					*files_init_input(t_files *files, char *filename);

// executor
void					ft_executor(t_cmd *cmd, int i);
void					close_pipe(t_cmd *cmd, int check);
void					duplication(t_cmd *cmd, t_executor *executor, int check,
							int i);
void					pipe_connect(t_cmd *cmd, t_executor *executor,
							int check, int i);
void					add_exec_node(t_cmd *cmd, t_executor **exec_list,
							char ***temp, int i);
t_files					*files_init(t_files *node);
char					*get_path(t_cmd *cmd, t_executor *exec);
void					wait_child_process(t_cmd *cmd, int check);
char					**clean_argv(char **str);
char					**fill_argv(char **arg);

// free
void					free_double(char **str);
void					free_triple(char ***str);
void					free_env_list(t_env *env_list);
void					free_dollar(char *dollar_before, char *dollar_after,
							char *dollar_value, char *line);
void					free_fd(t_cmd *cmd);
void					free_redirect(t_redirect **redirect);
void					free_executor(t_executor **executor);

// error
int						error_message(char *str);
void					executer_error(char **cmd, char *s, int exit_code);
void					file_error(t_executor *executor, t_files *files);

#endif
