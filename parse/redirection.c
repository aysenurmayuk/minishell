/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:11:35 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/14 14:34:03 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirection_check_helper(char *line)
{
	char *str;

	str = line;
	while (*str == ' ')
		str++;
	if (*str == '<' || *str == '>')
	{
		error_message("Error: syntax error near unexpected token\n");
		return ;
	}
}

void	redirection_check(t_cmd *str)
{
	char	*line;
	int 	in_quote;

	in_quote = 0;
	line = str->line;
	if (str->line[ft_strlen(str->line) - 1] == '<'
		|| str->line[ft_strlen(str->line) - 1] == '>')
	{
		error_message("Error: syntax error near unexpected token 'newline'\n");
		free(line);
		return ;
	}
	while (*line++)
	{
		while (*line && (in_quote != 0 || *line == '\'' || *line == '\"'))
			in_quote = ft_toggle_quote(*line++, in_quote);
		if ((*line == '<' || *line == '>') && ft_toggle_quote(*line, in_quote) == 0)
		{
			line++;
			if (*line == '<' || *line == '>')
				redirection_check_helper(line + 1);
			else
				redirection_check_helper(line);
		}
	}
}

