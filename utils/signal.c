/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:42:47 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/30 16:18:06 by kgulfida         ###   ########.fr       */
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
		exit(0);
	}
	else if (signo == SIGQUIT)
		return ;
	g_globals_exit = 0;
}

void	signal_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
