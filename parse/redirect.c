/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/26 16:28:41 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirect_type(char *str, int k)
{
	int	type;

	type = 0;
	if (str[k] == '>' && str[k + 1] == '>')
		type = APPEND;
	else if (str[k] == '<' && str[k + 1] == '<')
		type = HEREDOC;
	else if (str[k] == '>')
		type = OUTPUT;
	else if (str[k] == '<')
		type = INPUT;
	printf("%d\n", type);
}

int	check_redirect(char *command, int k, int in_quote)
{
	if ((command[k] == '<' || command[k] == '>') && in_quote == 0)
	{
		redirect_type(command, k);
		return (1);
	}
	return (0);
}

static void	handle_quotes(char **line, int *in_quote)
{
	while (**line && (*in_quote != 0 || **line == '\''
			|| **line == '\"'))
	{
		*in_quote = ft_toggle_quote(**line, *in_quote);
		(*line)++;
		if (*in_quote == '\'' || *in_quote == '\"')
			break ;
	}
}

void	redirect_handle(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	int		in_quote;
	char	*line;

	i = -1;
	in_quote = 0;
	while (cmd->command[++i])
	{
		j = -1;
		while (cmd->command[i][++j])
		{
			k = 0;
			line = cmd->command[i][j];
			while (cmd->command[i][j][k])
			{
				handle_quotes(&line, &in_quote);
				if (check_redirect(cmd->command[i][j], k, in_quote))
				{
				printf("%d\n",in_quote);
					printf("%s\n",cmd->command[i][j]);
					k++;
				}
				if(cmd->command[i][j][k])
					k++;
			}
		}
	}
}
