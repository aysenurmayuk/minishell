/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:32:11 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/21 19:15:50 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd, t_executor *executor)
{
	int	i;
	int	n;
	int	fd;

	n = 1;
	i = 1;
	fd = executor->files->fd_output;
	while (cmd->command[cmd->pipe_count - 1][i]
		&& ft_strcmp(cmd->command[cmd->pipe_count - 1][i], "-n") == 0)
	{
		if (i > 1 && cmd->command[cmd->pipe_count - 1][i + 1] == NULL)
			return ;
		n = 0;
		i++;
	}
	while (cmd->command[cmd->pipe_count - 1][i])
	{
		write(fd, remove_quotes(cmd, cmd->command[cmd->pipe_count - 1][i]),
			ft_strlen(remove_quotes(cmd, cmd->command[cmd->pipe_count
					- 1][i])));
		if (cmd->command[cmd->pipe_count - 1][i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (n)
		write(fd, "\n", 1);
	cmd->status = 0;
}
