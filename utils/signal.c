/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:42:47 by amayuk            #+#    #+#             */
/*   Updated: 2024/10/31 18:59:19 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    handle_sigint_main(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void    handle_sigint_heredoc(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    exit(130);
}
void    handle_sigint_child(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    exit(130);
}
void    signal_init(enum e_signal_mode mode)
{
    signal(SIGQUIT, SIG_IGN);
    if (mode == MAIN_MODE)
        signal(SIGINT, handle_sigint_main);
    else if (mode == HEREDOC_MODE)
        signal(SIGINT, handle_sigint_heredoc);
    else if (mode == CHILD_MODE)
        signal(SIGINT, handle_sigint_child);
    else
        signal(SIGINT, SIG_IGN);
}
