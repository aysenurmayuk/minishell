/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:42:47 by amayuk            #+#    #+#             */
/*   Updated: 2024/11/01 13:39:58 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int signo)
{
	if (g_globals_exit == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_globals_exit == IN_CAT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (g_globals_exit == IN_HERADOC)
	{
		write(1, "\n", 1);
		exit(1);
	}
	else if (signo == SIGQUIT)
		return ;
	g_globals_exit = 0;
}

void	signal_init(t_cmd *cmd)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if(g_globals_exit == IN_CAT)
		cmd->status = 130;
	else if (g_globals_exit == IN_HERADOC || g_globals_exit == IN_PARENT)
		cmd->status = 1;
}
