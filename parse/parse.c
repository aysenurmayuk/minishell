/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:57 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/14 17:04:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse(t_cmd *str)
{
	if(str->line[0] == '\0')
		return ;
	str->line = ft_strtrim(str->line, " ");
	quote_check(str);
	pipe_check(str);
	redirection_check(str);
	ft_split_space(str);
	dollar_handle(str);
	print_cmd(str);
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