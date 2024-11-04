/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 14:19:13 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_list(t_env **list, char *key, char *value)
{
	t_env	*current;

	current = *list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	export_both_list(t_cmd *cmd, char *cleaned, char *delimiter, char *key)
{
	char	*value;

	value = ft_strdup(delimiter + 1);
	key = ft_strndup(cleaned, delimiter - cleaned);
	if (search_list(&cmd->env, key, value) == 0)
		add_env_node(&cmd->env, ft_strdup(key), ft_strdup(value));
	if (search_list(&cmd->exp, key, value) == 0)
		add_env_node(&cmd->exp, ft_strdup(key), ft_strdup(value));
	free(value);
	free(key);
}

void	only_export(t_cmd *cmd, char *cleaned)
{
	char	*key;

	key = ft_strdup(cleaned);
	if (search_list(&cmd->exp, key, NULL) == 0)
		add_env_node(&cmd->exp, key, NULL);
	else
		free(key);
}
