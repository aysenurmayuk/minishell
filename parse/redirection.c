/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:11:35 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/17 20:35:38 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirection_check_helper(char *line)
{
	char *str;

	str = line;
	while (*str == ' ')
		str++;
	if (*str == '<' || *str == '>')
		return(error_message("Error: syntax error near unexpected token\n"));
	return (0);
}

int	redirection_check(t_cmd *str, char *line)
{
	int 	in_quote;

	in_quote = 0;
	if (str->line[ft_strlen(str->line) - 1] == '<'
		|| str->line[ft_strlen(str->line) - 1] == '>')
		return(error_message("Error: syntax error near unexpected token 'newline'\n"));
	while (*line++)
	{
		while (*line && (in_quote != 0 || *line == '\'' || *line == '\"'))
			in_quote = ft_toggle_quote(*line++, in_quote);
		if ((*line == '<' || *line == '>') && in_quote == 0)
		{
			line++;
			if (*line == '<' || *line == '>')
				return(redirection_check_helper(line + 1));
			else
				return(redirection_check_helper(line));
		}
	}
	return (0);
}

static void	redirect_name(t_cmd *str, int i, int j, int k)
{
	char *tmp;

	tmp = ft_substr(str->command[i][j], 0, k);
	if (str == NULL || str->command == NULL || str->command[i] == NULL || str->command[i][j] == NULL)
		return;
	if (str->command[i][j][k] == '>' && str->command[i][j][k + 1] == '>')
	{
		str->command[i][j] = ft_strjoin(tmp, ">>");
		free(tmp);
	}
	else if (str->command[i][j][k] == '<' && str->command[i][j][k + 1] == '<')
	{
		str->command[i][j] = ft_strjoin(tmp, "<<");
		free(tmp);
	}
	else if (str->command[i][j][k] == '>')
	{
		str->command[i][j] = ft_strjoin(tmp, ">");
		free(tmp);
	}
	else
	{
		str->command[i][j] = ft_strjoin(tmp, "<");
		free(tmp);
	}
}

void redirect(t_cmd *str, char *line)
{
	int i;
	int j;
	int k;
	int in_quote;

	i = 0;
	in_quote = 0;
	while (str->command[i] != NULL)
	{
		j = 0;
		while (str->command[i][j] != NULL)
		{
			k = 0;
			while (*line && (in_quote != 0 || *line == '\'' || *line == '\"'))
				in_quote = ft_toggle_quote(*line++, in_quote);
			while (str->command[i][j][k])
			{
				if ((str->command[i][j][k] == '>' || str->command[i][j][k] == '<') && in_quote == 0)
					redirect_name(str, i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
}

