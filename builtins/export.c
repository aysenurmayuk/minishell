/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:32 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/02 13:21:47 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export_list(t_cmd *cmd, t_env *env_list)
{
	t_env	*current;
	char	*temp;

	current = env_list;
	while (current)
	{
		if (current->value != NULL)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
		{
			temp = remove_quotes(cmd, current->key);
			printf("declare -x %s\n", temp);
			free(temp);
		}
		current = current->next;
	}
	cmd->status = 0;
}

static int	check_special_char(t_cmd *cmd, char *str)
{
	int	j;

	j = 1;
	if (str && !ft_isalpha(str[0]) && str[0] != '_')
	{
		executer_error_2(cmd->command[0], " not a valid identifier");
		cmd->status = 1;
		return (1);
	}
	while (str[j] && str[j] != '=')
	{
		if (ft_isalnum(str[j]) && str[j] != '_')
			j++;
		else
		{
			executer_error_2(cmd->command[0], "not a valid identifier");
			cmd->status = 1;
			return (1);
		}
	}
	return (0);
}

void	export_helper(t_cmd *cmd, char **export_value, char *cleaned, int i)
{
	int		check;
	char	*delimiter;

	while (export_value[i])
	{
		cleaned = remove_quotes(cmd, export_value[i]);
		check = check_special_char(cmd, cleaned);
		if (check == 1)
		{
			i++;
			continue ;
		}
		else if (check != 1)
		{
			delimiter = ft_strchr(cleaned, '=');
			if (delimiter)
				export_both_list(cmd, cleaned, delimiter);
			else
				only_export(cmd, cleaned);
		}
		free(cleaned);
		if (export_value[i])
			i++;
	}
}

void	ft_export(t_cmd *cmd)
{
	if (cmd->command[0][1] == NULL)
		print_export_list(cmd, cmd->exp);
	else
		export_helper(cmd, cmd->command[0], NULL, 1);
}
