/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:32 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/13 19:45:58 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r'))
		str++;
	return (str);
}

int	is_valid_identifier(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	key++;
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void	ft_export(t_cmd *cmd, char **key_value)
{
	char	*delimiter;
	char	*key;
	char	*value;
	t_env	*current;
	int		i;
	char	*trimmed_key_value;

	i = 0;
	value = NULL;
	while (key_value[++i])
	{
		trimmed_key_value = trim_whitespace(key_value[i]);
		delimiter = ft_strchr(trimmed_key_value, '=');
		if (delimiter)
			key = ft_strndup(trimmed_key_value, delimiter - trimmed_key_value);
		else
			key = ft_strdup(trimmed_key_value);
		if (!is_valid_identifier(key))
		{
			printf("export: `%s': not a valid identifier\n", key_value[i]);
			free(key);
			continue ;
		}
		if (!delimiter)
		{
			current = cmd->exp;
			value = ft_strdup("");
			while (current)
			{
				if (ft_strcmp(current->key, key) == 0)
					return ;
				current = current->next;
			}
			add_env_node(&cmd->exp, key, value);
		}
		else
		{
			value = ft_strdup(trim_whitespace(delimiter + 1));
			current = cmd->env;
			while (current)
			{
				if (ft_strcmp(current->key, key) == 0)
				{
					 free(current->value);
					// current->value = NULL;
					current->value = ft_strdup(value);
					printf("-------- %s\n",current->value);
					printf("çıktım**\n");
					//free(key);
					return ;
				}
				current = current->next;
			}
			add_env_node(&cmd->env, key, value);
			add_env_node(&cmd->exp, key, value);
			printf("çıktım\n");
		}
	}
}

void	print_export_list(t_cmd *cmd, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value != NULL)
		{
			printf("valuse:%s\n",current->value);
			// printf("key %s\n", current->key);
			// printf("declare -x %s=\"%s\"\n", current->key, current->value);
			
		}
		else
			printf("declare -x %s\n", remove_quotes(cmd, current->key));
		current = current->next;
	}
}
