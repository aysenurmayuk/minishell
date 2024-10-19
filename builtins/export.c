/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:32 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/19 18:20:40 by amayuk           ###   ########.fr       */
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
			{
				// free(current->value);
				current->value = ft_strdup(value);
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}


void	ft_export(t_cmd *cmd, char **key_value, char *trimmed_quote)
{
	char	*delimiter;
	char	*key;
	char	*value;
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
				continue ;
			}
		if (trimmed_quote)
		{
			delimiter = ft_strchr(trimmed_quote, '=');
			if (delimiter)
			{
				key = ft_strndup(trimmed_quote, delimiter - trimmed_quote);
				value = ft_strdup(delimiter + 1);
				flag = search_list(&cmd->env, key, value);
				if (flag == 0)
					add_env_node(&cmd->env, key, value);
				else
					search_list(&cmd->env, key, value);
				flag = search_list(&cmd->exp, key, value);
				if (flag == 0)
					add_env_node(&cmd->exp, key, value);
				else
					search_list(&cmd->exp, key, value);
			}
			else
			{
				key = ft_strdup(trimmed_quote);
				value = NULL;
				flag = search_list(&cmd->exp, key, value);
				if (flag == 0)
					add_env_node(&cmd->exp, key, value);
				else
					free(key);
			}
			i++;
		}
	}
}

void	print_export_list(t_cmd *cmd, t_env *env_list)
{
	t_env *current;

	current = env_list;
	while (current)
	{
		if (current->value != NULL)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", remove_quotes(cmd, current->key));
		current = current->next;
	}
}