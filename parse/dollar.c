/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/27 14:52:57 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dlr_special_char(char c)
{
	if ((c > 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97)
		|| (c > 122 && c < 127))
		return (1);
	return (0);
}

static char	*dollar_line(char *dollar_before, char *dollar_after,
		char *dollar_value)
{
	char	*line;
	char	*temp;

	if (!dollar_value)
		line = ft_strjoin(dollar_before, dollar_after);
	else
	{
		temp = ft_strjoin(dollar_before, dollar_value);
		line = ft_strjoin(temp, dollar_after);
		free(temp);
	}
	return (line);
}

static void	take_dollar_value(t_cmd *cmd, char **str, size_t *d, char *key)
{
	char	*dollar_before;
	char	*dollar_after;
	char	*dollar_value;
	char	*line;
	int		end;

	end = *(d) + 1;
	dollar_before = ft_substr(*str, 0, (*d));
	while ((*str)[end] && !(dlr_special_char((*str)[end])))
		end++;
	key = ft_substr(*str, (*(d) + 1), (end - (*(d) + 1)));
	dollar_value = get_env(cmd, key, NULL);
	dollar_after = ft_substr(*str, end, ft_strlen(*str + end));
	line = dollar_line(dollar_before, dollar_after, dollar_value);
	free(*str);
	*str = ft_strdup(line);
	free_dollar(dollar_before, dollar_after, dollar_value, line);
	free(key);
	*d = end - 1;
}

static void	is_dollar(t_cmd *cmd, int *i, int *j, size_t d)
{
	int		sq;
	int		dq;
	char	*str;

	sq = 0;
	dq = 0;
	str = cmd->command[*i][*j];
	while (str[d] != 0)
	{
		handle_quotes(str[d], &sq, &dq);
		if (str[d] == '$' && sq % 2 == 0)
		{
			if (str[d + 1] == '?')
				printf("soru işareti işlenecek"); // dollar_question();
			else
				take_dollar_value(cmd, &str, &d, NULL);
		}
		if (ft_strlen(str) <= d)
			break ;
		else
			d++;
	}
	cmd->command[*i][*j] = str;
}

int	dollar_handle(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->command[++i])
	{
		j = -1;
		while (cmd->command[i][++j])
			is_dollar(cmd, &i, &j, 0);
	}
	return (0);
}
