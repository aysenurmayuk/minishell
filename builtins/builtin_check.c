/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:51:35 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/31 21:51:47 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_handle(t_cmd *cmd, t_executor *executor)
{
	cmd->cleaned = remove_quotes(cmd, executor->argv[0]);
	if (ft_strcmp(cmd->cleaned, "exit") == 0)
		ft_exit(cmd);
	if (ft_strcmp(cmd->cleaned, "env") == 0 || ft_strcmp(cmd->cleaned,
			"ENV") == 0)
		print_env_list(cmd, cmd->env, executor);
	if (ft_strcmp(cmd->cleaned, "echo") == 0)
		ft_echo(cmd, executor);
	if (ft_strcmp(cmd->cleaned, "cd") == 0)
		ft_cd(cmd);
	if (ft_strcmp(cmd->cleaned, "pwd") == 0)
		ft_pwd(cmd);
	if (ft_strcmp(cmd->cleaned, "export") == 0)
		ft_export(cmd);
	if (ft_strcmp(cmd->cleaned, "unset") == 0)
	{
		ft_unset(&cmd->env, &cmd->command[0][1]);
		ft_unset(&cmd->exp, &cmd->command[0][1]);
		cmd->status = 0;
	}
	free(cmd->cleaned);
}

int	builtin_check(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0)
		return (2);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (3);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (4);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (5);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (6);
	else if (ft_strcmp(cmd, "export") == 0)
		return (7);
	else
		return (0);
}
