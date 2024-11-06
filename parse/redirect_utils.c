/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:29:19 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/05 19:47:19 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_variable(int *sq, int *dq, size_t *r)
{
	*sq = 0;
	*dq = 0;
	*r = 0;
}

void	init_redirect(t_files *files, t_executor *executor)
{
	t_redirect	*temp;

	temp = executor->redirect;
	while (temp)
	{
		if (temp->type == INPUT)
			files_init_input(files, temp->filename);
		else if (temp->type == APPEND)
			files_init_append(files, temp->filename);
		else if (temp->type == OUTPUT)
			files_init_output(files, temp->filename);
		if (files->error == 1 || files->error == 2)
			break ;
		temp = temp->next;
	}
}
