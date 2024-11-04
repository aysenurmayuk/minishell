/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 14:02:55 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	quote_check(t_cmd *cmd, char *line, int i)
{
	cmd->dquote_count = 0;
	cmd->squote_count = 0;
	cmd->dquote = false;
	cmd->squote = false;
	while (line[i])
	{
		if (line[i] == '\"' && cmd->squote != true)
		{
			cmd->dquote = true;
			cmd->dquote_count++;
			if (cmd->dquote_count % 2 == 0)
				cmd->dquote = false;
		}
		else if (line[i] == '\'' && cmd->dquote != true)
		{
			cmd->squote = true;
			cmd->squote_count++;
			if (cmd->squote_count % 2 == 0)
				cmd->squote = false;
		}
		i++;
	}
	if (cmd->dquote_count % 2 != 0 || cmd->squote_count % 2 != 0)
		return (error_message(cmd, "Error: There is open quote!\n"));
	return (0);
}

void	handle_quotes(char temp, int *squotes, int *dquotes)
{
	if (temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if (temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}

void	update_quote_counts(t_cmd *cmd, char ch)
{
	if (ch == '\"' && !cmd->squote)
	{
		cmd->dquote_count++;
		cmd->dquote = cmd->dquote_count % 2 == 1;
	}
	else if (ch == '\'' && !cmd->dquote)
	{
		cmd->squote_count++;
		cmd->squote = cmd->squote_count % 2 == 1;
	}
}

char	*create_cleaned_str(t_cmd *cmd, char *str, int sq, int dq)
{
	char	*cleaned;
	int		i;
	int		j;

	cleaned = (char *)malloc(sizeof(char) * (ft_strlen(str) - sq - dq + 1));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\"' && !cmd->squote) || (str[i] == '\''
				&& !cmd->dquote))
			update_quote_counts(cmd, str[i++]);
		else
			cleaned[j++] = str[i++];
	}
	cleaned[j] = '\0';
	return (cleaned);
}

char	*remove_quotes(t_cmd *cmd, char *str)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	cmd->idx = 0;
	cmd->dquote = false;
	cmd->squote = false;
	while (str[cmd->idx])
		handle_quotes(str[cmd->idx++], &sq, &dq);
	cmd->squote_count = 0;
	cmd->dquote_count = 0;
	return (create_cleaned_str(cmd, str, sq, dq));
}
