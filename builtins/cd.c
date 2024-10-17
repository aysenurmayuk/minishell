/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:48 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/17 20:08:30 by amayuk           ###   ########.fr       */
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
			printf("cd: %s: %s\n", home, strerror(errno));
	}
}

static void	update_pwd(t_cmd *cmd, char *oldpwd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(&(cmd->env), "OLDPWD", oldpwd);
		update_env_var(&(cmd->env), "PWD", cwd);
	}
	else
		printf("cd: error retrieving current directory: %s\n", strerror(errno));
}

void	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;

	oldpwd = get_env(cmd, "PWD", NULL);
	if (!cmd->command[0][1] || ft_strcmp(cmd->command[0][1], "~") == 0)
		change_to_home(cmd);
	else if (chdir(cmd->command[0][1]) != 0)
		printf("cd: %s: %s\n", cmd->command[0][1], strerror(errno));
	update_pwd(cmd, oldpwd);
	free(oldpwd);
}