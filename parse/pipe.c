/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/14 15:00:13 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_check(t_cmd *str)
{
	char *line;

	line = str->line;
	if (str->line[0] == '|' || str->line[ft_strlen(str->line) - 1] == '|')
		error_message("Error: syntax error near unexpected token '|'\n");
	while(*line)
	{
		if(*line == '|' || *line == '<' || *line == '>')
		{
			line++;
			if(*line == '<' || *line == '>')
				line++;
			while(*line == ' ')
				line++;
			if(*line == '|')
			{
				error_message("Error: syntax error near unexpected token '|'\n");
				break;
			}
		}
		line++;		
	}
	str->ncmd = ft_split2(str->line, '|');
}
