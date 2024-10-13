/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:32 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/13 15:18:36 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_cmd *cmd, char *key_value)
{
	char	*delimiter;
	char	*key;
	t_env	*current;
	char	*value;

	value = NULL;
	delimiter = ft_strchr(key_value, '=');
	if (!delimiter)
	{
		key = ft_strndup(key_value, delimiter - key_value);
		value = ft_strdup("");
		add_env_node(&cmd->exp, key, value);
		return ;
	}
	key = ft_strndup(key_value, delimiter - key_value);
	value = ft_strdup(delimiter + 1);
	current = cmd->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			free(key);
			return ;
		}
		current = current->next;
	}
	add_env_node(&cmd->env, key, value);
	add_env_node(&cmd->exp, key, value);
}

void	print_export_list(t_cmd *cmd, t_env *env_list)
{
	while (env_list)
	{
		if(env_list->value != NULL && ft_strcmp(env_list->value, "") != 0)
			printf("declare -x %s=\"%s\"\n", remove_quotes(cmd, env_list->key), remove_quotes(cmd, env_list->value));
		else
			printf("declare -x %s\n", remove_quotes(cmd, env_list->key));
		env_list = env_list->next;
	}
}