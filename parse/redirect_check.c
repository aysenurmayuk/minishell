/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:11:35 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/18 15:35:12 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_syntax_error(char *str)
{
	char	op;

	op = *str;
	if (*str == '<' || *str == '>')
	{
		str++;
		if (*str == op)
			str++;
		while (*str == ' ')
			str++;
		if (*str == '<' || *str == '>')
			return (
				error_message("Error: Redirect syntax error\n"));
	}
	return (0);
}

static int	redirect_check_helper(char *line)
{
	char	*str;

	str = line;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			if (check_syntax_error(str))
				return (1);
		}
		str++;
	}
	return (0);
}

int	redirect_check(t_cmd *str, char *line)
{
	int	in_quote;

	in_quote = 0;
	if (str->line[ft_strlen(str->line) - 1] == '<'
		|| str->line[ft_strlen(str->line) - 1] == '>')
		return (error_message("Error: Redirect syntax error\n"));
	while (*line++)
	{
		while (*line && (in_quote != 0 || *line == '\'' || *line == '\"'))
			in_quote = ft_toggle_quote(*line++, in_quote);
		if ((*line == '<' || *line == '>') && in_quote == 0)
		{
			return (redirect_check_helper(line));
		}
	}
	return (0);
}
