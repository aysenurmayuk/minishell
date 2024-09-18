/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/18 16:34:56 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirect_type(t_cmd *str, int i, int j, int k)
{
	int	type;

	while (str->command[i][j][k])
	{
		if (str->command[i][j][k] == '>' && str->command[i][j][k + 1] == '>')
		{
			type = APPEND;
			k++;
		}
		else if (str->command[i][j][k] == '<' && str->command[i][j][k
			+ 1] == '<')
		{
			type = HEREDOC;
			k++;
		}
		else if (str->command[i][j][k] == '>')
			type = OUTPUT;
		else if (str->command[i][j][k] == '<')
			type = INPUT;
		k++;
	}
	printf("%d\n", type);
}

void	redirect_handle(t_cmd *str, char *line)
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
			while (str->command[i][j][++k])
			{
				line = str->command[i][j];
				while (*line && (in_quote != 0 || *line == '\'' || *line == '\"'))
					in_quote = ft_toggle_quote(*line++, in_quote);
				if ((str->command[i][j][k] == '<' || str->command[i][j][k] == '>') && in_quote == 0)
				{
					redirect_type(str,i,j,k);
					k++;
				}
			}
		}
	}
}
