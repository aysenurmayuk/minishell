/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/09 18:03:01 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(char *line)
{
	char	*tmp;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	tmp = line;
	if (ft_strlen(line) != '\0' && (line[0] == '|' || line[ft_strlen(line) - 1] == '|'))
		return (error_message("Error: Pipe syntax error\n"));
	while (*line)
	{
		handle_quotes(*line, &sq, &dq);
		if ((*line == '|' || *line == '<' || *line == '>') && !sq && !dq)
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
