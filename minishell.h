/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysenurmayuk <aysenurmayuk@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:31 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/10 18:38:58 by aysenurmayu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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
# include <errno.h>

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

int						g_globals_exit;

typedef struct s_cmd
{
	// quote
	int idx;          // line index
	int dquote_count; // " sayısı
	int squote_count; // ' sayısı
	bool dquote;      // " açık mı
	bool squote;      // ' açık mı

	// parse
	char *line;      // gelen komut
	char **ncmd;     //	pipe ile ayrılmış komutlar
	char ***command; // komutlar
	int pipe_count;  // pipe sayısı
	char *cleaned; 

	struct s_env		*env;
	struct s_env		*exp;
	struct s_redirect	*redirect;
	pid_t				pid;
	// pwd
	int status; // exit status
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
	int					location;
	char *data; // heredoc data
	struct s_redirect	*prev;
	struct s_redirect	*next;
}						t_redirect;

void	print_cmd(t_cmd *str); // silinecek!!
void					print_env_list(t_env *env_list);
void					print_export_list(t_env *env_list);

// env
t_env					*create_env_node(char *key, char *value);
void					add_env_node(t_env **env_list, char *key, char *value);
void					parse_env(char **envp, t_env **env_list);

// utils
int						ft_strcmp(char *s1, char *s2);
char					*ft_strndup(const char *s, size_t n);
size_t					ft_strnlen(const char *src, size_t i);
char					**ft_split2(char const *s, char c);
void					ft_split_space(t_cmd *str);
int						ft_toggle_quote(char c, int in_quote);
void					handle_quotes(char temp, int *squotes, int *dquotes);

// builtins
int						special_char(char c);
void					builtin_check(t_cmd *cmd);
void					ft_exit(t_cmd *cmd);
void					ft_pwd(t_cmd *str);
void					ft_echo(t_cmd *cmd);
void					ft_cd(t_cmd *cmd);
void 			ft_unset(t_env **env_list, char *key);
void	ft_export(t_env **env_list, char *key_value);
void					parse_env(char **envp, t_env **env_list);
char					*get_env(t_cmd *cmd, char *key, char *dollar_value);

// parse
int						ft_parser(t_cmd *str);
int						quote_check(t_cmd *str, char *line);
int						pipe_check(char *line);
int						redirect_check(char *line);
void					redirect_handle(t_cmd *str);
// int		ft_wait_for_input(t_cmd *cmd); // heredoc için ? copilot dedi
int						dollar_handle(t_cmd *str);
char 					*remove_quotes(t_cmd *cmd, char *str);

// free
int						error_message(char *str);
void					ft_free_command(char ***str);
void					ft_free_ncmd(char **str);
void					free_env_list(t_env *env_list);
void					ft_full_free(t_cmd *str);
void					free_dollar(char *dollar_before, char *dollar_after,
							char *dollar_value, char *line);

#endif
