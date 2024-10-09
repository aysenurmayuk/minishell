/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/09 18:33:09 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char	*extract_filename(char *str)
{
	char	*filename;
	int		start;
	int		end;

	start = 0;
	while (str[start] && isspace(str[start]))
		start++;
	end = start;
	while (str[end] && !isspace(str[end]) && str[end] != '|' && str[end] != '<'
		&& str[end] != '>')
		end++;
	filename = malloc(end - start + 1);
	if (!filename)
		return (NULL);
	strncpy(filename, str + start, end - start);
	filename[end - start] = '\0';
	return (filename);
}

static int	redirect_type(t_cmd *cmd, char *str, int k)
{
	int	type;

	(void)cmd;
	type = 0;
	if (str[k] == '>' && str[k + 1] == '>')
		type = APPEND;
	else if (str[k] == '<' && str[k + 1] == '<')
		type = HEREDOC;
	else if (str[k] == '>')
		type = OUTPUT;
	else if (str[k] == '<')
		type = INPUT;
	return (type);
}

static void	is_redirect(t_cmd *cmd, int *i, int *j, size_t d)
{
	int		sq;
	int		dq;
	int		type;
	char	*str;
	char	*filename;

	sq = 0;
	dq = 0;
	filename = NULL;
	str = cmd->command[*i][*j];
	while (str[d] != 0)
	{
		handle_quotes(str[d], &sq, &dq);
		if ((str[d] == '<' || str[d] == '>') && sq % 2 == 0 && dq % 2 == 0)
		{
			type = redirect_type(cmd, str, d);
			if (str[d + 1] == '<' || str[d + 1] == '>')
				d++;
			if (str[d + 1] != '\0')
			{
				if ((type == APPEND || type == HEREDOC) && str[d + 1] != '\0')
					filename = extract_filename(str + d + 1);
				else if ((type == OUTPUT || type == INPUT)
					&& str[d + 1] != '\0')
					filename = extract_filename(str + d + 1);
			}
			else
				filename = extract_filename(cmd->command[*i][*j + 1]);
			printf("%d %s\n",type, filename);
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
