/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:48:39 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 16:00:10 by kgulfida         ###   ########.fr       */
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
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_triple(char ***str)
{
	int	i;
	// int	j;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free_double(str[i]);
	// {
	// 	j = -1;
	// 	while (str[i][++j])
	// 		free(str[i][j]);
	// 	free(str[i]);
	// }
	free(str);
}

void	free_double(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_full_free(t_cmd *str)
{
	free_triple(str->command);
	free_double(str->ncmd);
	free(str->line);
}