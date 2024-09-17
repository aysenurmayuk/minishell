/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/17 18:23:49 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(t_cmd *str, char *line)
{
	int 	in_quote;

	in_quote = 0;
	if (str->line[0] == '|' || str->line[ft_strlen(str->line) - 1] == '|')
		return(error_message("Error: syntax error near unexpected token '|'\n"));
	while(*line)
	{
		while (*line && (in_quote != 0 || *line == '\'' || *line == '\"'))
			in_quote = ft_toggle_quote(*line++, in_quote);
		if((*line == '|' || *line == '<' || *line == '>') && in_quote == 0)
		{
			line++;
			if(*line == '<' || *line == '>')
				line++;
			while(*line == ' ')
				line++;
			if(*line == '|')
			{
				return(error_message("Error: syntax error near unexpected token '|'\n"));
				break;
			}
		}
		line++;		
	}
	str->ncmd = ft_split2(str->line, '|');
	return (0);
}
