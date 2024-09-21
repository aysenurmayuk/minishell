/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:53:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/21 18:48:43 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_struct(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->redirect = NULL;
	cmd->env = NULL;
	cmd->exp = NULL;
	cmd->redirect = NULL;
}

static void	start_program(char **env, t_cmd *cmd)
{
	(void)env;
	while (1)
	{
		cmd->line = readline("minishell 🤯>");
		if (!cmd->line)
			break ;
		if (ft_strncmp(cmd->line, "exit", 5) == 0)
		{
			exit(0);
		}
		if (ft_strncmp(cmd->line, "env", 3) == 0)
		{
			print_env_list(cmd->env);
		}
		if (ft_strncmp(cmd->line, "export", 6) == 0)
		{
			print_export_list(cmd->env);
		}
		if (cmd->line) // alt satırları ekleme
			add_history(cmd->line);
		ft_parser(cmd);
		// if(!ft_parser(cmd))
		// 	continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd;

	(void)av;
	if (ac != 1)
	{
		error_message("This program does not accept arguments\n");
		exit(1);
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	reset_struct(cmd);
	// init_signal();
	parse_env(env, &cmd->env);
	parse_env(env, &cmd->exp);
	start_program(env, cmd);
	free_env_list(cmd->env);
	free_env_list(cmd->exp);
}
