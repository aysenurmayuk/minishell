/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:34:28 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/17 14:12:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_handle(t_cmd *cmd, t_executor *executor)
{
	if (cmd->command == NULL || cmd->command[0] == NULL)
		return ;
	cmd->cleaned = cmd->command[0][0];
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "exit") == 0)
		ft_exit(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "env") == 0
		|| ft_strcmp(remove_quotes(cmd, cmd->cleaned), "ENV") == 0)
		print_env_list(cmd, cmd->env);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "echo") == 0)
		ft_echo(cmd, executor);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "cd") == 0)
		ft_cd(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "pwd") == 0)
		ft_pwd(cmd);
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "export") == 0)
	{
		if (cmd->command[0][1] == NULL)
			print_export_list(cmd, cmd->exp);
		else
			ft_export(cmd, cmd->command[0], NULL);
	}
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "unset") == 0)
	{
		ft_unset(&cmd->env, cmd->command[0][1]);
		ft_unset(&cmd->exp, cmd->command[0][1]);
	}
}

int	builtin_check(t_cmd *cmd)
{
	cmd->cleaned = cmd->command[0][0];
	if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "exit") == 0)
		return (1);
	else if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "env") == 0
		|| ft_strcmp(remove_quotes(cmd, cmd->cleaned), "ENV") == 0)
		return (2);
	else if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "echo") == 0)
		return (3);
	else if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "cd") == 0)
		return (4);
	else if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "pwd") == 0)
		return (5);
	else if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "unset") == 0)
		return (6);
	else if (ft_strcmp(remove_quotes(cmd, cmd->cleaned), "export") == 0)
		return (7);
	else
		return (0);
}
