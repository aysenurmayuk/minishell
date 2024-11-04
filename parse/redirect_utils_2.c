/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:53:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 20:38:55 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	files_init_input(t_files *files, char *filename)
{
	int	fd;

	free(files->input);
	files->input = ft_strdup(filename);
	if (files->fd_input > 2)
		close(files->fd_input);
	fd = open(files->input, O_RDONLY, 0777);
	files->fd_input = fd;
	if (files->fd_input == -1)
		files->error = 1;
	free(filename);
}

void	files_init_output(t_files *files, char *filename)
{
	int	fd;

	free(files->output);
	files->output = ft_strdup(filename);
	if (files->fd_output > 2)
		close(files->fd_output);
	fd = open(files->output, O_CREAT | O_TRUNC | O_RDWR, 0777);
	files->fd_output = fd;
	if (files->fd_output == -1)
		files->error = 2;
	free(filename);
}

void	files_init_append(t_files *files, char *filename)
{
	int	fd;

	free(files->output);
	files->output = ft_strdup(filename);
	if (files->fd_output > 2)
		close(files->fd_output);
	fd = open(files->output, O_CREAT | O_APPEND | O_RDWR, 0777);
	files->fd_output = fd;
	if (files->fd_output == -1)
		files->error = 2;
	free(filename);
}

int	redirect_type(char *str, int r)
{
	int	type;

	type = 0;
	if (str[r] == '>' && str[r + 1] == '>')
		type = APPEND;
	else if (str[r] == '<' && str[r + 1] == '<')
		type = HEREDOC;
	else if (str[r] == '>')
		type = OUTPUT;
	else if (str[r] == '<')
		type = INPUT;
	return (type);
}
