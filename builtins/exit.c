/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysenurmayuk <aysenurmayuk@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:14:38 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/10 16:46:51 by aysenurmayu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_error(char *str, int status)
{
	printf("%s", str);
	exit(status);
}

void	ft_exit(t_cmd *cmd)
{
	if(cmd->pipe_count == 1)
	{
		if(cmd->command[0][1] == NULL)
			ft_exit_error("exit\n", 0);
		if(cmd->command[0][2] != NULL)
			ft_exit_error("exit\nminishell: exit: too many arguments\n", 1);
		else
		{
			if(ft_isnumeric(remove_quotes(cmd,cmd->command[0][1])))
			{
				g_globals_exit = ft_atoi(cmd->command[0][1]);
				g_globals_exit = g_globals_exit % 256;
				ft_exit_error("exit\n", g_globals_exit);
			}
			else
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", cmd->command[0][1]);
				exit(255);
			}
		}
	}
}
