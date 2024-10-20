/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:42:37 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/21 20:46:10 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_env **env_list, char *key)
{
	t_env	*prev;
	t_env	*current;

	if (!key || !*env_list)
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			//free(current->key);
			//free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}