/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:57 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/17 20:24:28 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_cmd *str)
{
	char *line;

	line = str->line;
	if(str->line[0] == '\0')
		return(1);
	str->line = ft_strtrim(str->line, " ");
	if(quote_check(str) || pipe_check(str, line) || redirection_check(str, line))
	{
		free(str->line);
		return (1);
	}
	ft_split_space(str);
	redirect(str, line);
	dollar_handle(str, line);
	print_cmd(str);
	return (0);
}

void	print_cmd(t_cmd *str)// silinecek fonksiyon
{
	int z;
	int y;
	z = 0;
	while (str->command[z] != NULL)
	{
		y = 0;
		printf("Command %d:\n", z);
		while (str->command[z][y] != NULL)
		{
			printf("  Arg %d: %s\n", y, str->command[z][y]);
			y++;
		}
		z++;
	}
}
