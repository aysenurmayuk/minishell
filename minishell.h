/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:31 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/14 16:17:32 by kgulfida         ###   ########.fr       */
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
	int					idx;
	int					dquote_count;
	int					squote_count;
	bool				dquote;
	bool				squote;

	char				*line;
	char				**ncmd;
	char				***command;
	int					pipe_count;

	struct s_env		*env;
	struct s_env		*exp;
	pid_t				pid;
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
	int					location;
	char				*data;
	struct s_redirect	*prev;
	struct s_redirect	*next;
}						t_redirect;

extern int				g_globals_exit;

void	print_cmd(t_cmd *str); // silinecek!!
void	print_env_list(t_env *env_list);

// env
t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **env_list, char *key, char *value);
void	parse_env(char **envp, t_env **env_list);

// utils
char	*ft_strndup(const char *s, size_t n);
size_t	t_strnlen(const char *src, size_t i);
char	**ft_split2(char const *s, char c);
void	ft_split_space(t_cmd *str);
int		ft_toggle_quote(char c, int in_quote);

// builtins
void	ft_exit(t_cmd *str);

// parse
void	ft_parse(t_cmd *str);
void	quote_check(t_cmd *str);
void	pipe_check(t_cmd *str);
void	redirection_check(t_cmd *str);
int		ft_wait_for_input(t_cmd *cmd);
void	dollar_handle(t_cmd *str);


// free
void	error_message(char *str);
void	reset_struct(t_cmd *cmd);

#endif
