/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/21 20:08:31 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_quotes(char **line, int *in_quote)
{
	while (**line && (*in_quote != 0 || **line == '\''
			|| **line != '\"'))
	{
		*in_quote = ft_toggle_quote(**line, *in_quote);
		(*line)++;
		if (*in_quote == '\'' || *in_quote == '\"')
			break ;
	}
}

int	dollar_handle(t_cmd *str, char *line)
{
	int	i;
	int	j;
	int	k;
	int	in_quote;

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
				handle_quotes(&line, &in_quote);
				if (str->command[i][j][k] == '$' && in_quote != 0)
					printf("olduğu gibi yazdırılacak\n");
				else if (str->command[i][j][k] == '$' && in_quote == 0)
					printf("işlenecek\n");
			}
		}
	}
	return (0);
}
