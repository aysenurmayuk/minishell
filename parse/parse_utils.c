/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:23:46 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/17 14:18:07 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//BU FONKSİYON SİLİNEBİLİR BAŞKA BİR FONKSİYONDA KULLANILMIYOR
int	ft_wait_for_input(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->line)
		return (2);
	while (cmd->line[i])
	{
		if ((cmd->line[i] != 10) && (cmd->line[i] != 32))
			return (1);
		i++;
	}
	return (0);
}
