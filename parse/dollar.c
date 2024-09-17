/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/17 18:23:25 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	dollar_handle(t_cmd *str, char *line)
{
	int		i;
	int		in_quote;

	i = -1;
	in_quote = 0;
	while (line[++i])
	{
		while (*line && ((in_quote != 0 && *line != '\"')|| *line == '\''))
		{
			in_quote = ft_toggle_quote(*line++, in_quote);
			if (in_quote == 0)
			{
				in_quote = 1;
				break;
			}
		}
		line = str->line;
		if (line[i] == '$' && in_quote == 1)
		{
			printf("girdim\n");
		}
		else if (line[i] == '$' && in_quote == 0)
		{
			printf("girmedim\n");
		}
	}
	return (0);
}
