/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/25 15:13:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_quotes(char **line, int *in_quote)
{
	while (**line && (*in_quote != 0 || **line == '\'' || **line != '\"'))
	{
		*in_quote = ft_toggle_quote(**line, *in_quote);
		(*line)++;
		if (*in_quote == '\'' || *in_quote == '\"')
			break ;
	}
}

static int	dlr_special_char(char c)
{
	if ((c > 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97)
		|| (c > 122 && c < 127))
		return (1);
	return (0);
}

static char	*take_dollar_value(t_cmd *cmd, char *str, int *k)
{
	char	key[7000];
	char	*value;
	char	temp[7000];
	int		i;
	int		end;
	int		start;
	t_env	*tmp;

	i = 0;
	end = *(k) + 1;
	start = end;
	// value = ft_strndup(str, (start - 1));
	while (str[end] && !(dlr_special_char(str[end])))
		end++;
	while (start < end)
		key[i++] = str[start++];
	key[i] = '\0';
	tmp = cmd->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			value = ft_strjoin(value, tmp->value);
		tmp = tmp->next;
	}
	while (str[end] && str[end] != '$')
		end++;
	i = 0;
	while (start < end)
		temp[i++] = str[start++];
	value = ft_strjoin(value, temp);
	return (value);
}

int	dollar_handle(t_cmd *str, char *line)
{
	int		i;
	int		j;
	int		k;
	int		in_quote;
	char	*dollar_value;

	i = -1;
	in_quote = 0;
	while (str->command[++i])
	{
		j = -1;
		while (str->command[i][++j])
		{
			k = -1;
			line = str->command[i][j];
			while (str->command[i][j][++k])
			{
				if (str->command[i][j][k] == '$' && in_quote == 0)
				{
					dollar_value = take_dollar_value(str, str->command[i][j], &k);
					printf("%s\n", dollar_value);
				}
				else if (str->command[i][j][k] == '$' && in_quote != 0)
					printf("olduğu gibi yazdırılacak\n");
				handle_quotes(&line, &in_quote);
			}
		}
	}
	return (0);
}
