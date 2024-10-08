/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysenurmayuk <aysenurmayuk@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/10 14:34:24 by aysenurmayu      ###   ########.fr       */
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
	if (ft_strlen(tmp) != '\0' && (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|'))
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
