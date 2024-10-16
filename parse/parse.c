/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:57 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/14 19:40:42 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_cmd *cmd)
{
	char	*line;

	if (cmd->line[0] == '\0')
		return (1);
	line = ft_strtrim(cmd->line, " ");
	if (quote_check(cmd, line) ||  redirect_check(line) || pipe_check(line) )
	{
		free(line);
		free(cmd->line);
		return (1);
	}
	cmd->ncmd = ft_split2(line, '|');
	ft_split_space(cmd);
	redirect_handle(cmd);
	dollar_handle(cmd);
	builtin_check(cmd);
	free(line);
	free(cmd->line);
	cmd->line = NULL;
	print_cmd(cmd);
	//ft_full_free(cmd);
	return (0);
}

void	print_cmd(t_cmd *str) // silinecek fonksiyon
{
	int z;
	int y;
	z = 0;
	while (str->command[z] != NULL)
	{
		y = 0;
		printf("Command %d:\n", z);
		while (str->command[z][y] != NULL)
		{
			printf("  Arg %d: %s\n", y, str->command[z][y]);
			y++;
		}
		z++;
	}
}
