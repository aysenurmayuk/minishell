/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:37 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/04 17:35:28 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_special_char_2(t_cmd *cmd, char *str)
{
	int	j;

	j = 1;
	if (str && !ft_isalpha(str[0]) && str[0] != '_' && str[0] != '-')
	{
		executer_error_2(cmd->command[0], " not a valid identifier");
		cmd->status = 1;
		return (1);
	}
	while (str[j])
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

void	ft_unset_helper(t_env **env_list, char **keys, int i)
{
	t_env	*prev;
	t_env	*current;

	while (keys && keys[i])
	{
		current = *env_list;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->key, keys[i]) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*env_list = current->next;
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	int		check;
	char	*cleaned;

	i = 0;
	while (cmd->command[0][i])
	{
		cleaned = remove_quotes(cmd, cmd->command[0][i]);
		check = check_special_char_2(cmd, cleaned);
		if (check == 1)
		{
			free(cleaned);
			i++;
			continue ;
		}
		else if (check != 1)
		{
			ft_unset_helper(&cmd->env, &cmd->command[0][i], 0);
			ft_unset_helper(&cmd->exp, &cmd->command[0][i], 0);
		}
		free(cleaned);
		if (cmd->command[0][i])
			i++;
	}
}
