/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:12:49 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/26 16:28:28 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_toggle_quote(char c, int in_quote)
{
	if (in_quote == 0 && (c == '\'' || c == '\"'))
		return (c);
	else if (in_quote == c)
		return (0);
	return (in_quote);
}

static size_t	ft_count(const char *str, char c)
{
	size_t	i;
	size_t	count;
	int		in_quote;

	i = 0;
	count = 0;
	in_quote = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c && !in_quote))
			i++;
		if (str[i] && (str[i] != c || in_quote))
		{
			count++;
			while (str[i] && (str[i] != c || in_quote))
			{
				in_quote = ft_toggle_quote(str[i], in_quote);
				i++;
			}
		}
	}
	return (count);
}

char	**ft_split2(char const *s, char c)
{
	size_t	str_i;
	size_t	start;
	size_t	end;
	char	**str;
	int		in_quote;

	start = 0;
	str_i = 0;
	in_quote = 0;
	str = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[start])
	{
		end = start;
		while (s[start] && (in_quote != 0 || s[start] != c))
			in_quote = ft_toggle_quote(s[start++], in_quote);
		if (start > end)
			str[str_i++] = ft_substr(s, end, start - end);
		if (s[start] != 0)
			start++;
	}
	str[str_i] = NULL;
	return (str);
}

void	ft_split_space(t_cmd *cmd)
{
	cmd->dquote = false;
	cmd->squote = false;
	cmd->idx = 0;
	cmd->pipe_count = 0;
	while (cmd->ncmd[cmd->pipe_count] != NULL)
		cmd->pipe_count++;
	cmd->command = (char ***)malloc((cmd->pipe_count + 1) * sizeof(char **));
	if (!cmd->command)
		return;
	while (cmd->ncmd[cmd->idx])
	{
		cmd->command[cmd->idx] = ft_split2(cmd->ncmd[cmd->idx], ' ');
		if (!cmd->command[cmd->idx])
		{
			while (cmd->idx-- > 0)
				free(cmd->command[cmd->idx]);
			free(cmd->command);
			return;
		}
		cmd->idx++;
	}
	cmd->command[cmd->pipe_count] = NULL;
}
