/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:37 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/30 20:03:43 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_env **env_list, char **keys)
{
	t_env	*prev;
	t_env	*current;
	int		i;

	i = 0;
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
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
}
