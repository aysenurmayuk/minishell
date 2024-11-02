/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:48:39 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/02 15:21:49 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		if(temp->key)
			free(temp->key);
		if(temp->value)
			free(temp->value);
		free(temp);
	}
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_triple(char ***str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!str)
		return ;
	while (str[++i])
		free_double(str[i]);
	while (str[j])
		str[j++] = NULL;
	free(str);
	str = NULL;
}

void	ft_full_free(t_cmd *str)
{
	free_triple(str->command);
	free_double(str->ncmd);
	free(str->line);
}
