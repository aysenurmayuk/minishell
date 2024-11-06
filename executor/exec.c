/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:52:46 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/06 11:12:11 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	open_pipe(t_cmd *cmd)
{
	int	**fd;
	int	i;

	i = -1;
	if (cmd->pipe_count == 0)
		return ;
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
	if (!cmd->fd)
	{
		return ;
	}
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
	if (check > 0 && cmd->pipe_count > 1)
	{
		builtin_handle(cmd, executor);
		exit(0);
	}
	path = get_path(cmd, executor);
	if (path == NULL && executor->argv[0] != NULL)
		executer_error(executor->argv, " command not found", 127);
	exit(0);
}

static void	executor_helper(t_cmd *cmd, t_executor *temp, int *check, int *i)
{
	if (temp->files->heredoc
		&& temp->files->fd_input < 2)
		temp->files->fd_input = -2;
	if (temp->argv && temp->argv[0])
	{
		*check = builtin_check(temp->argv[0]);
		if (*check > 0 && cmd->pipe_count == 1)
			builtin_handle(cmd, temp);
		else
		{
			g_globals_exit = 1;
			temp->pid = fork();
			if (temp->pid == 0)
				ft_execve(cmd, temp, *check, *i);
		}
		(*i)++;
	}
}

void	ft_executor(t_cmd *cmd, int i,int check, int flag)
{
	t_executor	*temp;

	open_pipe(cmd);
	temp = cmd->executor;
	while (temp)
	{
		if(flag == 1)
			heredoc_check(cmd, temp->files, 0, &flag);
		redirect_handle(cmd, temp, &i);
		cmd->status = 0;
		if (temp->redirect != NULL)
			init_redirect(temp->files, temp);
		if (temp->files->error == 1 || temp->files->error == 2)
		{
			file_error(cmd, temp, temp->files);
			temp = temp->next;
			i++;
			continue ;
		}
		executor_helper(cmd, temp, &check, &i);
		temp = temp->next;
	}
	close_pipe(cmd, check);
	free_executor(&cmd->executor);
}
