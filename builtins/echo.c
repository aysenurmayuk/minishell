/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:32:11 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/06 10:17:47 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_helper(char *str, char c)
{
	if(*str == '\0')
		return(0);
	while (*str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd, t_executor *executor)
{
	int	i;
	int	n;
	int	fd;

	n = 1;
	i = 1;
	fd = executor->files->fd_output;
	while (executor->argv[i] && executor->argv[i][0] == '-'
		&& echo_helper(&executor->argv[i][1], 'n'))
	{
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
