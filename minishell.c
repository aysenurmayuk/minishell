/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:53:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/02 20:51:57 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_struct(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->ncmd = NULL;
	cmd->command = NULL;
	cmd->cleaned = NULL;
	cmd->sep_path = NULL;
	cmd->env = NULL;
	cmd->envp = NULL;
	cmd->exp = NULL;
	cmd->executor = NULL;
	cmd->pipe_count = 0;
	cmd->status = 0;
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
        ft_executor(cmd, 0);
        // REDIRECT FREEELEEEEE !!!!!! free_redirect(&cmd->executor->redirect);
        free_double(cmd->sep_path);
		free_triple(cmd->command);
		free_double(cmd->ncmd);
		free_double(cmd->envp);
    }
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd;

	(void)av;
	if (ac != 1)
	{
		error_message("This program does not accept arguments\n");
		exit(0);
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	reset_struct(cmd);
	signal_init();
	parse_env(cmd, env, &cmd->env);
	parse_env(cmd, env, &cmd->exp);
	start_program(env, cmd);
	free_env_list(cmd->env);
	free_env_list(cmd->exp);
}
