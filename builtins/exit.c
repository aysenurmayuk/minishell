/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:14:38 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/10 13:57:01 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_cmd *str)
{
	int	exit_status;
	int	i;

	exit_status = 0;
	if (str->line && strcmp(str->line, "exit") == 0)
	{
		if (str->ncmd && str->ncmd[1])
			exit_status = atoi(str->ncmd[1]);
		free(str->line);
		if (str->ncmd)
		{
			i = 0;
			while (str->ncmd[i])
			{
				free(str->ncmd[i]);
				i++;
			}
			free(str->ncmd);
		}
		exit(exit_status);
	}
}