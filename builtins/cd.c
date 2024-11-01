/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:00:50 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/01 19:01:00 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env_node(env_list, key, value);
}
static void	change_to_home(t_cmd *cmd)
{
	char	*home;

	home = get_env(cmd, "HOME", NULL);
	if (home)
	{
		if (chdir(home) != 0)
		{
			executer_error_2(cmd->command[0], strerror(errno));
			cmd->status = 1;
		}
		else
			cmd->status = 0;
	}
}
static void	update_pwd(t_cmd *cmd, char *oldpwd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(&(cmd->env), "OLDPWD", oldpwd);
		update_env_var(&(cmd->env), "PWD", cwd);
		update_env_var(&(cmd->exp), "OLDPWD", oldpwd);
		update_env_var(&(cmd->exp), "PWD", cwd);
	}
	else
	{
		executer_error_2(cmd->command[0], strerror(errno));
		cmd->status = 1;
	}
}
void	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;

	oldpwd = get_env(cmd, "PWD", NULL);
	if (!cmd->command[0][1] || ft_strcmp(cmd->command[0][1], "~") == 0)
		change_to_home(cmd);
	else if (chdir(cmd->command[0][1]) != 0)
	{
		executer_error_2(cmd->command[0], strerror(errno));
		cmd->status = 1;
	}
	update_pwd(cmd, oldpwd);
	free(oldpwd);
}
