/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/25 14:39:51 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(char *line)
{
	char	*tmp;
	int		in_quote;

	in_quote = 0;
	tmp = line;
	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
		return (error_message("Error: Pipe syntax error\n"));
	while (*line)
	{
		while (*tmp && (in_quote != 0 || *tmp == '\'' || *tmp == '\"'))
			in_quote = ft_toggle_quote(*tmp++, in_quote);
		if ((*line == '|' || *line == '<' || *line == '>') && in_quote == 0)
		{
			line++;
			if (*line == '<' || *line == '>')
				line++;
			while (*line && *line == ' ')
				line++;
			if (*line == '|')
				return (error_message("Error: Pipe syntax error\n"));
		}
		if(*line)
			line++;
	}
	return (0);
}
