/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:57 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 13:00:28 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_cmd *cmd)
{
	char	*line;

	if (cmd->line[0] == '\0')
		return (1);
	line = ft_strtrim(cmd->line, " ");
	if (quote_check(cmd, line) || redirect_check(line) || pipe_check(line))
	{
		free(line);
		free(cmd->line);
		return (1);
	}
	cmd->ncmd = ft_split2(line, '|');
	cmd->envp = env_to_array(cmd->env);
	ft_split_space(cmd);
	dollar_handle(cmd);
	add_exec_node(cmd, &cmd->executor);
	redirect_handle(cmd);
	free(line);
	free(cmd->line);
	cmd->line = NULL;
	//print_cmd(cmd);
	return (0);
}

void	print_cmd(t_cmd *cmd) // silinecek fonksiyon
{
	int z;
	int y;
	z = 0;
	while (cmd->command[z] != NULL)
	{
		y = 0;
		printf("Command %d:\n", z);
		while (cmd->command[z][y] != NULL)
		{
			printf("  Arg %d: %s\n", y, cmd->command[z][y]);
			y++;
		}
		z++;
	}
}
