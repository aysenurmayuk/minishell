/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:36 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/18 16:36:52 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*dollar_line(char *dollar_before, char *dollar_after,
		char *dollar_value)
{
	char	*line;
	char	*temp;
	if (!dollar_value)
		dollar_value = ft_strdup("");

	temp = ft_strjoin(dollar_before, dollar_value);
	line = ft_strjoin(temp, dollar_after);
	free(temp);

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
	while ((*str)[end] && !(special_char((*str)[end])))
		end++;
	key = ft_substr(*str, (*(d) + 1), (end - (*(d) + 1)));
	dollar_value = get_env(cmd, key, NULL);
	dollar_value = get_env(cmd, key, NULL);
	if (!dollar_value)
		dollar_value = ft_strdup(""); // NULL ise boş string ata
	dollar_after = ft_substr(*str, end, ft_strlen(*str + end));
	line = dollar_line(dollar_before, dollar_after, dollar_value);
	free(*str);
	*str = ft_strdup(line);
	free_dollar(dollar_before, dollar_after, dollar_value, line);
	free(key);
	//*d = end - 1;
}

static void	dollar_question(char **str, size_t *d)
{
	char	*dollar_before;
	char	*dollar_after;
	char	*dollar_value;
	char	*line;

	dollar_before = ft_substr(*str, 0, (*d));
	dollar_value = ft_itoa(g_globals_exit);
	dollar_after = ft_substr(*str, (*d) + 2, ft_strlen((*str) + (*d) + 2));
	line = dollar_line(dollar_before, dollar_after, dollar_value);
	free(*str);
	*str = ft_strdup(line);
	free_dollar(dollar_before, dollar_after, dollar_value, line);
}

static void	is_dollar(t_cmd *cmd, int *i, int *j, size_t d)
{
    int		sq;
    int		dq;
    char		*str;
	// int dollar_count = 0;

    sq = 0;
    dq = 0;
    str = cmd->command[*i][*j];
    while (str[d] != '\0')
    {
        handle_quotes(str[d], &sq, &dq);
        if (str[d] == '$' && !sq)
        {
			// dollar_count++;
			// if (dollar_count % 2 == 0)
			// 	printf("dollar_count: %d\n", dollar_count);	
            if (str[d + 1] == '?')
                dollar_question(&str, &d);
            else
                take_dollar_value(cmd, &str, &d, NULL);
			if(str[d] == '$')
				continue;
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
