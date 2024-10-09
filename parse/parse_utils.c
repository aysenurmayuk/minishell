/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:23:46 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/09 18:04:53 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_char(char c)
{
	if ((c >= 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 97)
		|| (c > 122 && c < 127))
		return (1);
	return (0);
}

// //BU FONKSİYON SİLİNEBİLİR BAŞKA BİR FONKSİYONDA KULLANILMIYOR

// int	ft_wait_for_input(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (!cmd->line)
// 		return (2);
// 	while (cmd->line[i])
// 	{
// 		if ((cmd->line[i] != 10) && (cmd->line[i] != 32))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
