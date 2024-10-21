/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:45:22 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 16:03:06 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_dollar(char *dollar_before, char *dollar_after, char *dollar_value,
		char *line)
{
	free(line);
	free(dollar_before);
	free(dollar_after);
	free(dollar_value);
}

void	free_fd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->fd)
	{
		while (cmd->fd[i])
		{
			free(cmd->fd[i]);
			i++;
		}
		free(cmd->fd);
	}
	cmd->fd = NULL;
}
void	free_redirect(t_redirect **redirect)
{
	t_redirect	*temp;

	while (*redirect)
	{
		temp = *redirect;
		*redirect = (*redirect)->next;
		free(temp->filename);
		free(temp);
	}
	*redirect = NULL;
}

static void	free_files(t_files *files)
{
	if(files->heredoc)
		free(files->heredoc);
	free(files->output);
	free(files->input);
	free(files);
}

void	free_executor(t_executor **executor)
{
	t_executor	*temp;
	int			i;

	i = -1;
	while (*executor)
	{
		temp = *executor;
		*executor = (*executor)->next;
		free_double(temp->argv);
		free_files(temp->files);
		free(temp);
	}
	*executor = NULL;
}
