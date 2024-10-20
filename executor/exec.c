/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:52:46 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 19:24:09 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	open_pipe(t_cmd *cmd)
{
	int	**fd;
	int	i;

	i = -1;
	fd = (int **)malloc(sizeof(int *) * cmd->pipe_count);
	fd[cmd->pipe_count - 1] = NULL;
	while (++i < cmd->pipe_count - 1)
		fd[i] = malloc(sizeof(int) * 2);
	cmd->fd = fd;
	i = -1;
	while (++i < cmd->pipe_count - 1)
		pipe(cmd->fd[i]);
}

void	close_pipe(t_cmd *cmd, int check)
{
	int	i;

	i = 0;
	while (i < cmd->pipe_count - 1)
	{
		if (cmd->fd[i][0])
			close(cmd->fd[i][0]);
		if (cmd->fd[i][1])
			close(cmd->fd[i][1]);
		i++;
	}
	wait_child_process(cmd, check);
}

static void	ft_execve(t_cmd *cmd, t_executor *executor, int check, int i)
{
	char	*path;

	duplication(cmd, executor, check, i);
	if (check > 0 && cmd->pipe_count == 1)
	{
		builtin_handle(cmd, executor);
		exit(0); // fee(cmd->line); ??
	}
	path = get_path(cmd, executor);
	if (path == NULL && executor->argv[0] != NULL)
	{
		executer_error(executor->argv, "..command not found", 127);
	}
	exit(0);
}

void	ft_executor(t_cmd *cmd, int i)
{
	t_executor	*temp;
	int			check;

	open_pipe(cmd);
	temp = cmd->executor;
	while (temp)
	{
		check = builtin_check(cmd);
		if (temp->argv)
		{
			if (check > 0 && cmd->pipe_count == 1)
				builtin_handle(cmd, temp);
			else
			{
				g_globals_exit = 1;
				temp->pid = fork();
				if (temp->pid == 0)
					ft_execve(cmd, temp, check, i);
			}
			i++;
		}
		temp = temp->next;
	}
	close_pipe(cmd, check);
	free_executor(&cmd->executor);
}
