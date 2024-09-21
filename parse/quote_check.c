/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:07:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/21 19:14:12 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(t_cmd *str, char *line)
{
	str->idx = 0;
	str->dquote_count = 0;
	str->squote_count = 0;
	str->dquote = false;
	str->squote = false;
	while (line[str->idx])
	{
		if(line[str->idx] == '\"' && str->squote != true)
		{
			str->dquote = true;
			str->dquote_count++;
			if(str->dquote_count % 2 == 0)
				str->dquote = false;
		}
		else if(line[str->idx] == '\'' && str->dquote != true)
		{
			str->squote = true;
			str->squote_count++;
			if(str->squote_count % 2 == 0)
				str->squote = false;
		}
		str->idx++;
	}
	if(str->dquote_count % 2 != 0 || str->squote_count % 2 != 0)
		return (error_message("Error: There is open quote!\n"));
	return (0);
}
