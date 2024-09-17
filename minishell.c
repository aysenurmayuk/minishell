/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:53:54 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/17 14:23:52 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_program(char **env, t_cmd *cmd)
{
	(void)env;
	while (1)
	{
		cmd->line = readline("minishell 🤯>");
		if (!cmd->line)
			break ;
		if (cmd->line && ft_wait_for_input(cmd) == 1)
			add_history(cmd->line);
		ft_parse(cmd);
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
	parse_env(env, &cmd->env);
	parse_env(env, &cmd->exp);
	// init_signal();
	start_program(env, cmd);
	// free fonksiyonu yazılacak!!
}
