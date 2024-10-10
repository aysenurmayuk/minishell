/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysenurmayuk <aysenurmayuk@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:11:35 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/10 14:34:36 by aysenurmayu      ###   ########.fr       */
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
			return (error_message("Error: Redirect syntax error!\n"));
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

int	redirect_check(char *line)
{
	char	*tmp;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	tmp = line;
	if (ft_strlen(tmp) != '\0' && (tmp[ft_strlen(tmp) - 1] == '<' || tmp[ft_strlen(tmp) - 1] == '>'))
		return (error_message("Error: Redirect syntax error\n"));
	
	while (*line)
	{
		handle_quotes(*line, &sq, &dq);
		if ((*line == '<' || *line == '>') && !sq && !dq)
			return (redirect_check_helper(line));
		line++;
	}
	return (0);
}
