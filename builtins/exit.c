/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:14:38 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/09 14:32:24 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_exit(t_cmd *str)
// {
// 	int	exit_status;
// 	int	i;

// 	exit_status = 0;
// 	if (str->line && strcmp(str->line, "exit") == 0)
// 	{
// 		if (str->ncmd && str->ncmd[1])
// 			exit_status = atoi(str->ncmd[1]);
// 		free(str->line);
// 		if (str->ncmd)
// 		{
// 			i = 0;
// 			while (str->ncmd[i])
// 			{
// 				free(str->ncmd[i]);
// 				i++;
// 			}
// 			free(str->ncmd);
// 		}
// 		exit(exit_status);
// 	}
// }

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
			if(ft_isnumeric(cmd->command[0][1]))
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
