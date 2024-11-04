/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:27:10 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 20:25:27 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_connect(t_cmd *cmd, t_executor *executor, int check, int i)
{
	if (cmd->executor == executor)
		dup2(cmd->fd[i][1], STDOUT_FILENO);
	else if (executor->next == NULL)
		dup2(cmd->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(cmd->fd[i - 1][0], STDIN_FILENO);
		dup2(cmd->fd[i][1], STDOUT_FILENO);
	}
	close_pipe(cmd, check);
}

void	wait_child_process(t_cmd *cmd, int check)
{
	t_executor	*tmp;
	int			result;

	tmp = cmd->executor;
	while (tmp)
	{
		waitpid(tmp->pid, &result, 0);
		if (!(check > 0) && tmp->files->error != 1 && tmp->files->error != 2)
		{
			if (WIFSIGNALED(result) && WTERMSIG(result) == SIGINT)
				cmd->status = 130;
			cmd->status = result / 256;
		}
		tmp = tmp->next;
	}
	if (cmd->executor)
		free_fd(cmd);
}

void	duplication(t_cmd *cmd, t_executor *executor, int check, int i)
{
	t_files	*files;
	int		fd[2];

	files = executor->files;
	if (cmd->pipe_count > 1)
		pipe_connect(cmd, executor, check, i);
	if (files->fd_input == -2)
	{
		pipe(fd);
		write(fd[1], files->heredoc, ft_strlen(files->heredoc));
		close(fd[1]);
		if (ft_strcmp(executor->argv[0], "cat") == 0)
		{
			close(files->fd_heredoc[1]);
			dup2(files->fd_heredoc[0], STDIN_FILENO);
			close(files->fd_heredoc[0]);
		}
		if (executor->next || ft_strcmp(executor->argv[0], "echo"))
			dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
	}
	if (files->fd_output >= 2)
		dup2(files->fd_output, STDOUT_FILENO);
	if (files->fd_input >= 2)
		dup2(files->fd_input, STDIN_FILENO);
}

static void	file_check_exec(t_cmd *cmd, t_executor *exec)
{
	struct stat	file;

	if (stat(exec->argv[0], &file) == 0)
	{
		if (S_ISREG(file.st_mode))
		{
			if (file.st_mode & S_IXUSR)
			{
				execve(exec->argv[0], exec->argv, cmd->envp);
				exit(0);
			}
			else
				executer_error(exec->argv, " permission denied", 126);
		}
		else if (ft_strcmp(exec->argv[0], ".") == 0)
			executer_error(exec->argv, " filename argument required", 2);
		else if (ft_strcmp(cmd->executor->argv[0], "..") == 0)
			executer_error(exec->argv, " commond not found", 127);
		else
			executer_error(exec->argv, " is a directory", 126);
	}
}

char	*get_path(t_cmd *cmd, t_executor *exec)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	if (exec->argv[0] == NULL)
		return (NULL);
	if (exec->argv[0][0] == '/' || exec->argv[0][0] == '.')
		file_check_exec(cmd, exec);
	while (cmd->sep_path[i])
	{
		temp = ft_strjoin(cmd->sep_path[i], "/");
		command = ft_strjoin(temp, exec->argv[0]);
		free(temp);
		if (access(command, X_OK) == 0)
			execve(command, exec->argv, cmd->envp);
		free(command);
		i++;
	}
	return (NULL);
}
