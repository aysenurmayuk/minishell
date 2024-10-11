/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:32:11 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/11 18:44:17 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n;

	n = 1;
	i = 1;
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
		printf("%s", remove_quotes(cmd, cmd->command[cmd->pipe_count - 1][i]));
		if (cmd->command[cmd->pipe_count - 1][i + 1])
			printf(" ");
		i++;
	}
	if (n)
		printf("\n");
}
