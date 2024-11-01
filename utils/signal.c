/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:54:15 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/01 18:55:50 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    signal_handler(int signo)
{
    (void)signo;
    if (g_globals_exit == 0 || g_globals_exit == 23)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_globals_exit = 23;
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
}

void    signal_init(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
