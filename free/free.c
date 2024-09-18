/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:48:39 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/18 15:31:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_struct(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->env = NULL;
	cmd->exp = NULL;
}

int	error_message(char *str)
{
	printf("%s", str);
	// system("leaks minishell");
	// exit(1);
	return (1);
}

