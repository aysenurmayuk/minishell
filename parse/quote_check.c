/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/27 14:49:20 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(t_cmd *cmd, char *line)
{
	cmd->idx = 0;
	cmd->dquote_count = 0;
	cmd->squote_count = 0;
	cmd->dquote = false;
	cmd->squote = false;
	while (line[cmd->idx])
	{
		if(line[cmd->idx] == '\"' && cmd->squote != true)
		{
			cmd->dquote = true;
			cmd->dquote_count++;
			if(cmd->dquote_count % 2 == 0)
				cmd->dquote = false;
		}
		else if(line[cmd->idx] == '\'' && cmd->dquote != true)
		{
			cmd->squote = true;
			cmd->squote_count++;
			if(cmd->squote_count % 2 == 0)
				cmd->squote = false;
		}
		cmd->idx++;
	}
	if(cmd->dquote_count % 2 != 0 || cmd->squote_count % 2 != 0)
		return (error_message("Error: There is open quote!\n"));
	return (0);
}

void	handle_quotes(char temp, int *squotes, int *dquotes)
{
	if (temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if (temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}
