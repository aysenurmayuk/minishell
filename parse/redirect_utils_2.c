/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:53:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/19 18:18:57 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_output(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_open_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

t_files	*files_init_input(t_files *node, char *arg)
{
	free(node->input);
	node->input = ft_strdup(arg);
	if (node->fd_input > 2)
		close(node->fd_input);
	node->fd_input = ft_open_input(node->input);
	if (node->fd_input == -1)
		node->error = 1;
	return (node);
}

t_files	*files_init_output(t_files *node, char *arg)
{
	free(node->output);
	node->output = ft_strdup(arg);
	if (node->fd_output > 2)
		close(node->fd_output);
	node->fd_output = ft_open_output(node->output);
	if (node->fd_output == -1)
		node->error = 2;
	return (node);
}

t_files	*files_init_append(t_files *node, char *arg)
{
	free(node->output);
	node->output = ft_strdup(arg);
	if (node->fd_output > 2)
		close(node->fd_output);
	node->fd_output = ft_open_append(node->output);
	if (node->fd_output == -1)
		node->error = 2;
	return (node);
}

