/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:32:11 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/31 20:08:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd, t_executor *executor)
{
	int		i;
	int		n;
	int		fd;
	char	*temp;

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
		temp = remove_quotes(cmd, executor->argv[i]);
		write(fd, temp, ft_strlen(temp));
		free(temp);
		if (executor->argv[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (n)
		write(fd, "\n", 1);
	cmd->status = 0;
}
