/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:34:28 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/11 18:42:55 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_check(t_cmd *cmd)
{
	cmd->cleaned = cmd->command[0][0];
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "exit") == 0)
		ft_exit(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "env") == 0)
		print_env_list(cmd->env);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "echo") == 0)
		ft_echo(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "cd") == 0)
		ft_cd(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "pwd") == 0)
		ft_pwd(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "unset") == 0)
		ft_unset(&cmd->env, cmd->command[0][1]);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "export") == 0 && cmd->command[0][1] == NULL)
		print_export_list(cmd->env);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "export") == 0 && cmd->command[0][1] != NULL)
		ft_export(&cmd->env, cmd->command[0][1]);
}