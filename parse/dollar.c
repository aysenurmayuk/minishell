/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/26 20:18:18 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	handle_quotes(char **line, int *in_quote)
// {
// 	while (**line)
// 	{
// 		*in_quote = ft_toggle_quote(**line, *in_quote);
// 		(*line)++;
// 		if (*in_quote != 0)  // Tırnak açıldığında dur
// 			break ;
// 	}
// }

static void	handle_quotes(char temp, int *squotes, int *dquotes)
{
	if (temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if (temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}

static int	dlr_special_char(char c)
{
	if ((c > 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97)
		|| (c > 122 && c < 127))
		return (1);
	return (0);
}

static char *dollar_line(char *dollar_before, char	*dollar_after, char	*dollar_value)
{
	char	*line;
	char	*temp;
	
	if(!dollar_value)
		line = ft_strjoin(dollar_before, dollar_after);
	else
	{
		temp = ft_strjoin(dollar_before, dollar_value);
		line = ft_strjoin(temp, dollar_after);
		free(temp);
	}
	return(line);
}

static void	take_dollar_value(t_cmd *cmd, char **str, size_t *d)
{
	char	*key;
	char	*dollar_before;
	char	*dollar_after;
	char	*dollar_value;
	char	*line;
	int		i;
	int		end;
	int		start;
	t_env	*tmp;

	i = 0;
	end = *(d) + 1;
	start = end;
	dollar_before = ft_substr(*str, 0, (*d));
	while ((*str)[end] && !(dlr_special_char((*str)[end])))
		end++;
	key = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
		key[i++] = (*str)[start++];
	key[i] = '\0';
	tmp = cmd->env;
	dollar_value = NULL;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			dollar_value = ft_strdup(tmp->value);
			break;
		}
		tmp = tmp->next;
	}
	if(!dollar_value)
		dollar_value = ft_strdup("");
	dollar_after = ft_substr(*str, end, ft_strlen(*str + end));
	line = dollar_line(dollar_before, dollar_after, dollar_value);
	free(*str);
	*str = ft_strdup(line);
	free(line);
    free(dollar_before);
    free(dollar_after);
    free(key);
    free(dollar_value);
	*d = end - 1;
}

static void	is_dollar(t_cmd *cmd, char *str, int sq, int dq)
{
	size_t	d;

	d = 0;
	while (str[d] != 0)
	{
		handle_quotes(str[d], &sq, &dq);
		if (str[d] == '$' && sq % 2 == 0)
		{
			if(str[d + 1] == '?')
				printf("soru işareti işlenecek"); //dollar_question();
			else
				take_dollar_value(cmd, &str, &d);
		}
		if(ft_strlen(str) <= d)
			break;
		else
			d++;
	}
	printf("%s\n", str);
}

int	dollar_handle(t_cmd *cmd)
{
	int		i;
	int		j;

	i = -1;
	while (cmd->command[++i])
	{
		j = -1;
		while (cmd->command[i][++j])
			is_dollar(cmd, cmd->command[i][j], 0, 0);
	}
	return (0);
}
