/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubra <kubra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/15 16:26:01 by kubra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(t_cmd *cmd, char *line)
{
	cmd->idx = 0;
	cmd->dquote_count = 0;
	cmd->squote_count = 0;
	cmd->dquote = false;
	cmd->squote = false;
	while (line[cmd->idx])
	{
		if(line[cmd->idx] == '\"' && cmd->squote != true)
		{
			cmd->dquote = true;
			cmd->dquote_count++;
			if(cmd->dquote_count % 2 == 0)
				cmd->dquote = false;
		}
		else if(line[cmd->idx] == '\'' && cmd->dquote != true)
		{
			cmd->squote = true;
			cmd->squote_count++;
			if(cmd->squote_count % 2 == 0)
				cmd->squote = false;
		}
		cmd->idx++;
	}
	if(cmd->dquote_count % 2 != 0 || cmd->squote_count % 2 != 0)
		return (error_message("Error: There is open quote!\n"));
	return (0);
}

void	handle_quotes(char temp, int *squotes, int *dquotes)
{
	if (temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if (temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}


char *remove_quotes(t_cmd *cmd, char *str)
{
    int 	i = 0;
	int		j = 0;
	int 	sq = 0;
	int		dq = 0;
	char	*cleaned;

	cmd->idx = 0;
	cmd->dquote = false;
	cmd->squote = false;
	while (str[cmd->idx++])
		handle_quotes(str[cmd->idx], &sq, &dq);
	cleaned = (char *)malloc(sizeof(char) * (ft_strlen(str) - sq - dq + 1));
    // if (!cleaned)
    //     return (NULL);
	while (str[i]) 
	{
		if (str[i] == '\"' && !cmd->squote)
		{
			cmd->dquote_count++;
			cmd->dquote = cmd->dquote_count % 2 == 1;
			i++;
		}
		else if (str[i] == '\'' && !cmd->dquote)
		{
			cmd->squote_count++;
			cmd->squote = cmd->squote_count % 2 == 1;
			i++;
		}
		else 
		{
            cleaned[j++] = str[i++];
        }
    }
    cleaned[j] = '\0';
    return cleaned;
}


// void clean_quote(t_cmd *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (cmd->command[i])
// 	{
// 		j = 0;
// 		while (cmd->command[i][j])
// 			cmd->cleaned[i][j] = remove_quotes(cmd, cmd->command[i][j]);
// 			j++;
// 		i++;
// 	}

// }
