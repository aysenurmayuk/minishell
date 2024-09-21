/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:31 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/21 19:14:40 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
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

typedef struct s_cmd
{
	// quote
	int					idx; // line index
	int					dquote_count; // " sayısı
	int					squote_count; // ' sayısı
	bool				dquote; // " açık mı
	bool				squote; // ' açık mı

	//parse
	char				*line; // gelen komut
	char				**ncmd; //	pipe ile ayrılmış komutlar
	char				***command; // komutlar
	int					pipe_count; // pipe sayısı

	struct s_env		*env;
	struct s_env		*exp;
	struct s_redirect	*redirect;
	pid_t				pid;
	//pwd
	int					status; // exit status
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_redirect
{
	int					type; // 10: heredoc, 11: append, 12: input, 13: output
	int					location; // 0: stdin, 1: stdout, 2: stderr
	char				*data; // heredoc data
	struct s_redirect	*prev;
	struct s_redirect	*next;
}						t_redirect;

extern int				g_globals_exit;

void	print_cmd(t_cmd *str); // silinecek!!
void	print_env_list(t_env *env_list); 
void	print_export_list(t_env *env_list);


// env
t_env	*create_env_node(char *key, char *value); 
void	add_env_node(t_env **env_list, char *key, char *value);
void	parse_env(char **envp, t_env **env_list);

// utils
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strnlen(const char *src, size_t i);
char	**ft_split2(char const *s, char c);
void	ft_split_space(t_cmd *str);
int		ft_toggle_quote(char c, int in_quote);

// builtins
void	ft_exit(t_cmd *str); 
void	ft_pwd(t_cmd *str);
void	parse_env(char **envp, t_env **env_list);


// parse
int		ft_parser(t_cmd *str); 
int		quote_check(t_cmd *str, char *line);
int		pipe_check(char *line);
int		redirect_check(char *line); 
void 	redirect_handle(t_cmd *str);
//int		ft_wait_for_input(t_cmd *cmd); // heredoc için ? copilot dedi
int		dollar_handle(t_cmd *str, char *line);


// free
int		error_message(char *str);
void	ft_free_command(char ***str);
void	ft_free_ncmd(char **str);
void	free_env_list(t_env *env_list);
void	ft_full_free(t_cmd *str);




#endif
