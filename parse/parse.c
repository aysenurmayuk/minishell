/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:57 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 15:26:57 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_cmd *cmd)
{
	char	*line;

	if (cmd->line[0] == '\0')
		return (1);
	line = ft_strtrim(cmd->line, " ,\t");
	free(line);
	if (line[0] == '\0')
		return (1);
	if (quote_check(cmd, line, 0) || redirect_check(cmd, line)
		|| pipe_check(cmd, line, 0, 0))
	{
		free(line);
		free(cmd->line);
		line = NULL;
		cmd->line = NULL;
		return (1);
	}
	cmd->ncmd = ft_split2(cmd->new_line, '|');
	cmd->envp = env_to_array(cmd->env, NULL, 0, 0);
	ft_split_space(cmd);
	dollar_handle(cmd);
	add_exec_node(cmd, &cmd->executor, NULL, 0);
	ft_executor(cmd, 0);
	return (0);
}
