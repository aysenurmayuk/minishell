/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:09:01 by amayuk            #+#    #+#             */
/*   Updated: 2024/09/17 15:10:53 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd *str)
{
	char	*c;

	c = getcwd(NULL, 0);
	if (!c)
	{
		perror("getcwd");
		str->status = BUILTIN;
		return;
	}
	printf("%s\n", c);
	free(c);
}