/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:15:29 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/06 12:49:24 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_message(t_cmd *cmd, char *str)
{
	cmd->status = 258;
	printf("%s", str);
	return (1);
}

void	executer_error_2(char **cmd, char *s)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ":", 1);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	executer_error(char **cmd, char *s, int exit_code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ":", 1);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(exit_code);
}

// static void	free_redirect_next(t_redirect *redirect)
// {
// 	t_redirect	*temp;

// 	while (redirect)
// 	{
// 		printf("**%s\n", temp->filename);
// 		temp = redirect;
// 		redirect = redirect->next;
// 		free(temp->filename);
// 		free(temp);
// 	}
// 	redirect = NULL;
// }

void	file_error(t_cmd *cmd, t_executor *executor, t_files *files)
{
	(void)files;
	if (files->error == 2)
		perror(files->output);
	else if (files->error == 1)
		perror(files->input);
	free_double(executor->argv);
	executor->argv = NULL;
	if (executor->files->heredoc)
		free(executor->files->heredoc);
	free(executor->files->input);
	free(executor->files->output);
	free(executor->files);
	// if (executor->redirect->next)
	// 	free_redirect_next(executor->redirect->next);
	executor->files = files_init(executor->files);
	executor->files->error = 1;
	cmd->status = 1;
}
