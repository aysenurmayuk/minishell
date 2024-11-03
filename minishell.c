/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:53:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/03 18:53:16 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_struct(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->new_line = NULL;
	cmd->ncmd = NULL;
	cmd->command = NULL;
	cmd->cleaned = NULL;
	cmd->sep_path = NULL;
	cmd->envp = NULL;
	cmd->pipe_count = 0;
}

static void start_program(char **env, t_cmd *cmd)
{
    (void)env;
    while (1)
    {
        g_globals_exit = 0;
        sep_path(cmd);
        cmd->line = readline("minishellcik>");
        if (!cmd->line)
        {
            printf("exit\n");
            break ;
        }
        if(g_globals_exit == 23)
        {
            cmd->status = 1;
            g_globals_exit = 0;
        }
        if (cmd->line && wait_for_input(cmd) == 1)
            add_history(cmd->line);
        ft_parser(cmd);
        // REDIRECT FREEELEEEEE !!!!!! free_redirect(&cmd->executor->redirect);
        full_free(cmd);
    }
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd;

	(void)av;
	if (ac != 1)
	{
		error_message(NULL, "This program does not accept arguments\n");
		exit(0);
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	reset_struct(cmd);
	signal_init();
	cmd->env = NULL;
	cmd->exp = NULL;
	cmd->executor = NULL;
	cmd->status = 0;
	parse_env(cmd, env, &cmd->env);
	parse_env(cmd, env, &cmd->exp);
	start_program(env, cmd);
	free_env_list(cmd->env);
	free_env_list(cmd->exp);
}
