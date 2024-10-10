/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysenurmayuk <aysenurmayuk@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:32:11 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/10 16:24:32 by aysenurmayu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int i;
	int n;

	n = 1;
	i = 1; 
	if (cmd->command[cmd->pipe_count - 1][i] && ft_strcmp(cmd->command[cmd->pipe_count - 1][i], "-n") == 0)
	{
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
