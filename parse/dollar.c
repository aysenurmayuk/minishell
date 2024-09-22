/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/22 18:48:24 by kgulfida         ###   ########.fr       */
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

static void	dollar_take_value(t_cmd *cmd, char *str, int *k)
{
	char	temp[7000];
	int		i;
	int		end;
	int		start;
	int		len;
	t_env	*tmp;

	i = 0;
	end = *(k) + 1;
	start = end;
	while (str[end] && !(dlr_special_char(str[end])))
		end++;
	len = end - start;
	while (start < end)
		temp[i++] = str[start++];
	temp[i] = '\0';
	tmp = cmd->env;
	while(tmp)
	{
		if(ft_strncmp(temp, tmp->key, len) == 0 && tmp->key[len] == '\0')
			printf("%s\n", tmp->value); //execve fonksiyonuna gönderilecek!!
		tmp = tmp->next;
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
					dollar_take_value(str, str->command[i][j], &k);
			}
		}
	}
	return (0);
}
