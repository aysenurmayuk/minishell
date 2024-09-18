/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/18 16:05:38 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			while (*line && ((in_quote != 0 && *line != '\"') || *line == '\''))
			{
				in_quote = ft_toggle_quote(*line++, in_quote);
				if (in_quote == 0)
				{
					in_quote = 1;
					break ;
				}
			}
			while (str->command[i][j][++k])
			{
				if (str->command[i][j][k] == '$' && in_quote != 0)
				{
					printf("olduğu gibi yazdırılacak\n");
				}
				else if (str->command[i][j][k] == '$' && in_quote == 0)
				{
					printf("işlenecek\n");
				}
			}
		}
	}
	return (0);
}
