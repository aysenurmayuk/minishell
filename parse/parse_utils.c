/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:23:46 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 20:30:11 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_char(char c)
{
	if ((c >= 32 && c < 48) || (c > 57 && c < 65) || (c > 90 && c < 95)
		|| (c > 122 && c < 127))
		return (1);
	return (0);
}

void	sep_path(t_cmd *cmd)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)) == 0)
		{
			cmd->sep_path = ft_split(tmp->value, ':');
			return ;
		}
		tmp = tmp->next;
	}
	cmd->sep_path = ft_split("", ':');
}

int	wait_for_input(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->line)
		return (2);
	while (cmd->line[i])
	{
		if ((cmd->line[i] != 10) && (cmd->line[i] != 32))
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}
