/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:31 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/06 14:12:31 by kgulfida         ###   ########.fr       */
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
# define IN_CAT 1
# define IN_HERADOC 2
# define IN_PARENT 3
# define HEREDOC 10
# define APPEND 11
# define INPUT 12
# define OUTPUT 13
# define C_PROCESS 101
# define M_PROCESS 100
# define HEREDOC_PROECESS 102
# define BUFFER_SIZE 42

int	g_globals_exit;

typedef struct s_cmd
{
	int					idx;
	int					dquote_count;
	int					squote_count;
	bool				dquote;
	bool				squote;
	char				*line;
	char				*new_line;
	char				**ncmd;
	char				***command;
	char				*cleaned;
	char				**sep_path;
	int					pipe_count;
	int					status;
	int					flag_exp;
	int					flag_env;
	int					check;
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
	int					type;
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

t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **env_list, char *key, char *value);
char	*get_env(t_cmd *cmd, char *key, char *dollar_value);
void	print_env_list(t_cmd *cmd, t_env *env_list, t_executor *executor);
char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, int n);
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strnlen(const char *src, size_t i);
int		ft_isspace(char c);
char	**ft_split2(char const *s, char c);
void	ft_split_space(t_cmd *str);
int		ft_toggle_quote(char c, int in_quote);
void	handle_quotes(char temp, int *squotes, int *dquotes);
void	signal_init(void);
int		special_char(char c);
int		builtin_check(char *cmd);
void	builtin_handle(t_cmd *cmd, t_executor *executor);
void	ft_exit(t_cmd *cmd);
void	ft_pwd(t_cmd *str);
void	ft_echo(t_cmd *cmd, t_executor *executor);
void	ft_cd(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_export(t_cmd *cmd);
void	only_export(t_cmd *cmd, char *cleaned);
void	export_both_list(t_cmd *cmd, char *cleaned, char *delimiter, char *key);
void	parse_env(t_cmd *cmd, char **envp, t_env **env_list);
char	*remove_quotes(t_cmd *cmd, char *str);
char	**env_to_array(t_env *env_list, t_env *temp, int i, int count);
void	sep_path(t_cmd *cmd);
void	init_redirect(t_files *files, t_executor *executor);
void	init_variable(int *sq, int *dq, size_t *r);
int		ft_parser(t_cmd *str, char *line);
int		wait_for_input(t_cmd *cmd);
int		quote_check(t_cmd *cmd, char *line, int i);
int		pipe_check(t_cmd *cmd, char *line, int sq, int dq);
int		wait_for_input(t_cmd *cmd);
int		dollar_handle(t_cmd *str);
int		redirect_check(t_cmd *cmd, char *line);
void	redirect_handle(t_cmd *cmd, t_executor *temp, int *i);
void	heredoc_check(t_cmd *cmd, t_files *files, int i, int *flag);
void	files_init_append(t_files *files, char *filename);
void	files_init_output(t_files *files, char *filename);
void	files_init_input(t_files *files, char *filename);
int		redirect_type(char *str, int r);
void	ft_executor(t_cmd *cmd, int i, int check, int flag);
void	close_pipe(t_cmd *cmd, int check);
void	duplication(t_cmd *cmd, t_executor *executor, int check, int i);
void	pipe_connect(t_cmd *cmd, t_executor *executor, int i);
void	add_exec_node(t_cmd *cmd, t_executor **exec_list, char ***temp, int i);
t_files	*files_init(t_files *node);
char	*get_path(t_cmd *cmd, t_executor *exec);
void	wait_child_process(t_cmd *cmd, int check);
char	**clean_argv(t_cmd *cmd, char **str);
char	**fill_argv(char **arg);
void	reset_struct(t_cmd *cmd);
void	full_free(t_cmd *cmd);
void	free_double(char **str);
void	free_triple(char ***str);
void	free_env_list(t_env *env_list);
void	free_dollar(char *dollar_before, char *dollar_after,
			char *dollar_value, char *line);
void	free_fd(t_cmd *cmd);
void	free_redirect(t_redirect **redirect);
void	free_executor(t_executor **executor);
int		error_message(t_cmd *cmd, char *str);
void	executer_error(char **cmd, char *s, int exit_code);
void	executer_error_2(char **cmd, char *s);
void	file_error(t_cmd *cmd, t_executor *executor, t_files *files);
#endif