/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:32:11 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/01 15:33:04 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd, t_executor *executor)
{
	int		i;
	int		n;
	int		fd;

	n = 1;
	i = 1;
	fd = executor->files->fd_output;
	while (executor->argv[i] && ft_strcmp(executor->argv[i], "-n") == 0)
	{
		if (i > 1 && executor->argv[i + 1] == NULL)
			return ;
		n = 0;
		i++;
	}
	while (executor->argv[i])
	{
		write(fd, executor->argv[i], ft_strlen(executor->argv[i]));
		if (executor->argv[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (n)
		write(fd, "\n", 1);
	cmd->status = 0;
}
