/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:34:28 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/30 15:37:28 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_check(t_cmd *cmd)
{
	if (strncmp(cmd->line, "exit", 4) == 0)
	{
		ft_exit(cmd);
	}
	if (ft_strncmp(cmd->line, "env", 3) == 0)
	{
		print_env_list(cmd->env);
	}
	if (ft_strncmp(cmd->line, "export", 6) == 0)
	{
		print_export_list(cmd->env);
	}
}