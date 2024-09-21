/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:57 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/21 19:13:31 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_cmd *str)
{
	char	*line;

	if (str->line[0] == '\0')
		return (1);
	line = ft_strtrim(str->line, " ");
	if (quote_check(str, line) || pipe_check(line) || redirect_check(line))
	{
		free(line);
		free(str->line);
		return (1);
	}
	str->ncmd = ft_split2(line, '|');
	free(line);
	free(str->line);
	str->line = NULL;
	ft_split_space(str);
	redirect_handle(str);
	dollar_handle(str, line);
	print_cmd(str);
	ft_full_free(str);
	return (0);
}

void	print_cmd(t_cmd *str) // silinecek fonksiyon
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
