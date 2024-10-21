/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:15:29 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 15:50:21 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_message(char *str)
{
	printf("%s", str);
	return (1);
}

void	executer_error(char **cmd, char *s, int exit_code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ":", 1);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(exit_code);
}
