/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:09:01 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/30 17:54:53 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd *str)
{
	char *c;

	c = getcwd(NULL, 0);
	if (!c)
	{
		perror("getcwd");
		str->status = 1;
		return ;
	}
	printf("%s\n", c);
	str->status = 0;
	free(c);
}
