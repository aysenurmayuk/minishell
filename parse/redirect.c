/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/30 20:03:27 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *extract_filename(char *str)
{
    char *filename;
    int start;
    int end;

    // Boşlukları atla
    start = 0;
    while (str[start] && isspace(str[start]))
        start++;

    // Dosya adının sonunu bul (boşluk, pipe, ya da başka bir yönlendirme sembolü olana kadar)
    end = start;
    while (str[end] && !isspace(str[end]) && str[end] != '|' && str[end] != '<' && str[end] != '>')
        end++;

    // Dosya adını ayır
    filename = malloc(end - start + 1);
    if (!filename)
        return NULL;
    
    strncpy(filename, str + start, end - start);
    filename[end - start] = '\0';  // Null sonlandırma

    return filename;
}

static void	redirect_type(t_cmd *cmd, char *str, int k)
{
	int	type;
	char *filename;
	(void)cmd;

	type = 0;
	filename = NULL;
	if (str[k] == '>' && str[k + 1] == '>')
		type = APPEND;
	else if (str[k] == '<' && str[k + 1] == '<')
		type = HEREDOC;
	else if (str[k] == '>')
		type = OUTPUT;
	else if (str[k] == '<')
		type = INPUT;
	if((type == APPEND || type == HEREDOC) && str[k + 2] != '\0')
		filename = extract_filename(str + k + 2);
	else if((type == OUTPUT || type == INPUT) && str[k + 1] != '\0')
		filename = extract_filename(str + k + 1);
	printf("%s\n", filename);
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
			redirect_type(cmd, str, d);
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
