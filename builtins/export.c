/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:32 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/11 19:05:19 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_env **env_list, char *key_value)
{
	char	*delimiter;
	char	*key;
	t_env	*current;
	char	*value;

	value = NULL;
	delimiter = ft_strchr(key_value, '=');
	if (!delimiter)
	{
		key = ft_strdup(key_value);
		value = ft_strdup("");
		add_env_node(env_list, key, value);
		return ;
	}
	key = ft_strndup(key_value, delimiter - key_value);
	value = ft_strdup(delimiter + 1);
	current = *env_list;
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
	add_env_node(env_list, key, value);
}
