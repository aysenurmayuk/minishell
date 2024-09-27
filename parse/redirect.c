/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/27 16:12:58 by kgulfida         ###   ########.fr       */
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

static void	is_redirect(t_cmd *cmd, int *i, int *j, size_t d)
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
		if ((str[d] == '<' || str[d] == '>') && sq % 2 == 0 && dq % 2 == 0)
		{
			redirect_type(str, d);
			if((str[d] == '<' || str[d] == '>'))
				d++;
		}
		if (ft_strlen(str) <= d)
			break ;
		else
			d++;
	}
	cmd->command[*i][*j] = str;
}

void	redirect_handle(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->command[++i])
	{
		j = -1;
		while (cmd->command[i][++j])
			is_redirect(cmd, &i, &j, 0);
	}
}
