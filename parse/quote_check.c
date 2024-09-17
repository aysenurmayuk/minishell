/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/13 17:13:24 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_check(t_cmd *str)
{
	str->idx = 0;
	str->dquote_count = 0;
	str->squote_count = 0;
	str->dquote = false;
	str->squote = false;
	while (str->line[str->idx])
	{
		if(str->line[str->idx] == '\"' && str->squote != true)
		{
			str->dquote = true;
			str->dquote_count++;
			if(str->dquote_count % 2 == 0)
				str->dquote = false;
		}
		else if(str->line[str->idx] == '\'' && str->dquote != true)
		{
			str->squote = true;
			str->squote_count++;
			if(str->squote_count % 2 == 0)
				str->squote = false;
		}
		str->idx++;
	}
	if(str->dquote_count % 2 != 0 || str->squote_count % 2 != 0)
		error_message("Error: There is open quote!\n"); //error mesaj fonksiyonu yazılacak!!!!!!
}

// int	between_quote(t_cmd *str)
// {
// 	int i;

// 	i = 0;
// 	str->idx = 0;
// 	str->dquote_count = 0;
// 	str->squote_count = 0;
// 	while(str->line[str->idx++])
// 	{
// 		if(str->line[str->idx] == '|')
// 		{
// 			while(i++ < str->idx)
// 			{
// 				if(str->line[i] == '\"')
// 					str->dquote_count++;
// 				else if(str->line[i] == '\'')
// 					str->squote_count++;
// 			}
// 			if(str->squote_count % 2 != 0 && str->dquote_count % 2 != 0)
// 				return (0);
// 		}
// 	}
// 	return (1);
// }
