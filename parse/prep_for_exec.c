/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:33:27 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/06 15:45:57 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_files	*files_init(t_files *node)
{
	node = (t_files *)malloc(sizeof(t_files));
	node->error = 0;
	node->output = NULL;
	node->input = NULL;
	node->heredoc = NULL;
	node->fd_input = 0;
	node->fd_output = 1;
	return (node);
}

static t_executor	*create_exec_node(t_cmd *cmd, char **command)
{
	t_executor	*new_node;

	new_node = malloc(sizeof(t_executor));
	if (!new_node)
		return (NULL);
	new_node->argv = clean_argv(cmd, fill_argv(command));
	new_node->files = files_init(new_node->files);
	new_node->redirect = NULL;
	new_node->pid = -1;
	new_node->next = NULL;
	return (new_node);
}

void	add_exec_node(t_cmd *cmd, t_executor **exec_list, char ***temp, int i)
{
	t_executor	*new_node;
	t_executor	*tmp_node;

	temp = cmd->command;
	if (cmd->command == NULL || cmd->command[i] == NULL)
		return ;
	while (temp[i] != NULL)
	{
		new_node = create_exec_node(cmd, temp[i]);
		if (new_node == NULL)
		{
			cmd->status = 0;
			return ;
		}
		if (*exec_list == NULL)
			*exec_list = new_node;
		else
		{
			tmp_node = *exec_list;
			while (tmp_node->next)
				tmp_node = tmp_node->next;
			tmp_node->next = new_node;
		}
		i++;
	}
}

char	**env_to_array(t_env *env_list, t_env *temp, int i, int count)
{
	char	**env_array;
	char	*env_str;

	temp = env_list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	temp = env_list;
	while (temp)
	{
		env_str = ft_strjoin(temp->key, "=");
		env_array[i] = ft_strjoin(env_str, temp->value);
		free(env_str);
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
