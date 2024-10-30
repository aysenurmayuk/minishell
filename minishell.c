/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:53:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/30 20:51:24 by kgulfida         ###   ########.fr       */
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
	cmd->exp = NULL;
	cmd->executor = NULL;
	cmd->status = 0;
}

static void	start_program(char **env, t_cmd *cmd)
{
	(void)env;
	while (1)
	{
		sep_path(cmd);
		cmd->line = readline("minishell 🤯>");
		if (!cmd->line)
		{
			printf("exit\n");
			break;
		}
		if (cmd->line && wait_for_input(cmd) == 1)
			add_history(cmd->line);
		ft_parser(cmd);
		ft_executor(cmd, 0);
		//free_redirect(&cmd->executor->redirect);
		free_double(cmd->sep_path);
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
