/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:29:19 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/02 15:28:06 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int take_status(t_cmd *cmd, t_files *files, int pid)
{
    int status;
    g_globals_exit = IN_PARENT;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        cmd->status = 1;
    else
        cmd->status = WEXITSTATUS(status);
    close(files->fd_heredoc[1]);
    if (cmd->status != 0)
        return (3);
    else
        return (0);
}

void	handle_heredoc_helper(t_files *files, char *line)
{
	if (line == NULL)
	{
		close(files->fd_heredoc[1]);
		exit(0);
	}
	if (ft_strcmp(line, files->input) == 0)
	{
		free(line);
		exit(0);
	}
	write(files->fd_heredoc[1], line, ft_strlen(line));
	write(files->fd_heredoc[1], "\n", 1);
	free(line);
}

int	handle_heredoc(t_cmd *cmd,t_files *files)
{
	char	*line;
	int		pid;
	int		status;

	pipe(files->fd_heredoc);
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		g_globals_exit = IN_HERADOC;
		while (1)
		{
			line = readline(">");
			handle_heredoc_helper(files, line);
		}
	}
	else
		status = take_status(cmd, files, pid);
	return (status);
}

void	files_init_heredoc(t_cmd *cmd,t_files *files, char *filename)
{
	files->heredoc = ft_strdup("");
	free(files->input);
	files->input = ft_strdup(filename);
	files->error = handle_heredoc(cmd , files);
	if (files->error == 1)
		return ;
	free(files->heredoc);
	files->heredoc = get_next_line(files->fd_heredoc[0]);
	close(files->fd_heredoc[0]);
}

t_files	*init_redirect(t_cmd *cmd, t_files *files, t_executor *executor)
{
	t_redirect	*temp;
	
	files = files_init(files);	
	temp = cmd->executor->redirect;
	while (temp)
	{
		if (temp->type == HEREDOC)
			files_init_heredoc(cmd, files, temp->filename);
		temp = temp->next;
	}
	temp = executor->redirect;
	while (temp)
	{
		if (temp->type == INPUT)
			files = files_init_input(files, temp->filename);
		else if (temp->type == APPEND)
			files = files_init_append(files, temp->filename);
		else if (temp->type == OUTPUT)
			files = files_init_output(files, temp->filename);
		if(files->error == 2)
			return(files);
		temp = temp->next;
	}
	return(files);
}
