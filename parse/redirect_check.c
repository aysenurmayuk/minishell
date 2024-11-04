/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:11:35 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 17:50:43 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_space(char *input, int sq, int dq)
{
	int	len;
	int	i;
	int	j;

	len = (int)ft_strlen(input);
	char *result = malloc(len * 3 + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		handle_quotes(input[i], &sq, &dq);
		if ((input[i] == '>' || input[i] == '<') && (i == 0 || input[i
				- 1] != '\\') && sq % 2 == 0 && dq % 2 == 0)
		{
			if (j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
			result[j++] = input[i];
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
					&& input[i + 1] == '<'))
			{
				result[j++] = input[i + 1];
				i++;
			}
			if (input[i + 1] != ' ' && input[i + 1] != '\0')
				result[j++] = ' ';
		}
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static int	check_syntax_error(t_cmd *cmd, char *str)
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
			return (error_message(cmd, "Error: Redirect syntax error!\n"));
	}
	return (0);
}

static int	redirect_check_helper(t_cmd *cmd, char *line)
{
	char	*str;

	str = line;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			if (check_syntax_error(cmd, str))
				return (1);
		}
		str++;
	}
	return (0);
}

int	redirect_check(t_cmd *cmd, char *line)
{
	char	*tmp;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	tmp = line;
	if (ft_strlen(tmp) != '\0' && (tmp[ft_strlen(tmp) - 1] == '<'
			|| tmp[ft_strlen(tmp) - 1] == '>'))
		return (error_message(cmd, "Error: Redirect syntax error\n"));
	cmd->new_line = add_space(line, 0, 0);
	while (*line)
	{
		handle_quotes(*line, &sq, &dq);
		if ((*line == '<' || *line == '>') && sq % 2 == 0 && dq % 2 == 0)
		{
			return (redirect_check_helper(cmd, line));
		}
		line++;
	}
	return (0);
}
