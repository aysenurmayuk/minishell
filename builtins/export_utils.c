/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/31 18:09:47 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	search_list(t_env **list, char *key, char *value)
{
	t_env	*current;

	current = *list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
				current->value = ft_strdup(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	export_both_list(t_cmd *cmd, char *cleaned, char *delimiter)
{
	char *key;
	char *value;
	int flag_env;
	int flag_exp;

	key = ft_strndup(cleaned, delimiter - cleaned);
	value = ft_strdup(delimiter + 1);
	flag_env = search_list(&cmd->env, key, value);
	if (flag_env == 0)
		add_env_node(&cmd->env, key, value);
	flag_exp = search_list(&cmd->exp, key, value);
	if (flag_exp == 0)
		add_env_node(&cmd->exp, key, value);
}

void	only_export(t_cmd *cmd, char *cleaned)
{
	char *key;
	char *value;
	int flag_exp;
	
	key= ft_strdup(cleaned);
	value = NULL;
	flag_exp = search_list(&cmd->exp, key, value);
	if(flag_exp == 0)
		add_env_node(&cmd->exp, key, value);
}
