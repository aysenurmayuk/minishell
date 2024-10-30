/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:53:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/30 17:38:51 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_files	*files_init_input(t_files *files, char *filename)
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
	return (files);
}

t_files	*files_init_output(t_files *files, char *filename)
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
	return (files);
}

t_files	*files_init_append(t_files *files, char *filename)
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
	return (files);
}
