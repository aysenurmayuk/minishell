/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:32 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/14 21:14:21 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	search_list(t_env *list, char *key, char *value)
{
	t_env	*current;

	current = list;
	while (current)
	{
		if (current->value && ft_strcmp(current->key, key) == 0)
		{
			printf("%s\n", current->value);
			free(current->value);
			current->value = ft_strdup(value);
			printf("%s\n", current->value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_export(t_cmd *cmd, char **key_value)
{
	char	*delimiter;
	char	*key;
	char	*value;
	char	*trimmed_quote;
	int		i;
	int		flag;

	i = 1;
	while (key_value[i] != NULL)
	{
		trimmed_quote = remove_quotes(cmd, key_value[i]);
		if (trimmed_quote && !ft_isalpha(trimmed_quote[0])
			&& trimmed_quote[0] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				key_value[i]);
			i++;
		}
		if (trimmed_quote)
		{
			delimiter = ft_strchr(trimmed_quote, '=');
			if (delimiter)
			{
				key = ft_strndup(trimmed_quote, delimiter - trimmed_quote);
				value = ft_strdup(delimiter + 1);
				flag = search_list(cmd->env, key, value);
				if (flag == 0)
				{
					add_env_node(&cmd->env, key, value);
					add_env_node(&cmd->exp, key, value);
				}
			}
			else if (!delimiter)
			{
				key = ft_strdup(trimmed_quote);
				flag = search_list(cmd->exp, key, NULL);
				if (flag == 0)
					add_env_node(&cmd->exp, key, NULL);
			}
			i++;
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
			// printf("%s\n", current->value);
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", remove_quotes(cmd, current->key));
		current = current->next;
	}
}
