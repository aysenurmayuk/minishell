/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 17:47:39 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(t_cmd *cmd, char *line, int sq, int dq)
{
	char	*tmp;

	tmp = line;
	if (ft_strlen(tmp) != '\0' && (tmp[0] == '|'
			|| tmp[ft_strlen(tmp) - 1] == '|'))
		return (error_message(cmd, "Error: Pipe syntax error\n"));
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
				return (error_message(cmd, "Error: Pipe syntax error\n"));
		}
		if (*line)
			line++;
	}
	return (0);
}
