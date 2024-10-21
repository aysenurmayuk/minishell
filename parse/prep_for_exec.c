/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:33:27 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 17:04:44 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_files	*files_init(t_files *node)
{
	node = (t_files *)malloc(sizeof(t_files));
	node->error = 0;
	node->output = ft_strdup("");
	node->input = ft_strdup("");
	node->heredoc = NULL;
	node->fd_input = 0;
	node->fd_output = 1;
	return (node);
}

char	**command_init(char **command)
{
	char	**dest;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (command[len])
		len++;
	dest = (char **)malloc(sizeof(char *) * (len + 1));
	dest[len + 1] = NULL;
	i = -1;
	j = 0;
	while (command[++i])
	{
		if ((ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
			&& (ft_strchr(command[i], '\"') || ft_strchr(command[i], '\'')))
			dest[j++] = ft_substr(command[i], 1, ft_strlen(command[i] - 2));
		else
			dest[j++] = ft_strdup(command[i]);
	}
	free_double(command);
	return (dest);
}

static t_executor	*create_exec_node(char **command)
{
	t_executor	*new_node;

	new_node = malloc(sizeof(t_executor));
	if (!new_node)
		return (NULL);
	new_node->argv = command_init(fill_argv(command));
	new_node->pid = -1; //?
	new_node->files = files_init(new_node->files);
	new_node->next = NULL;
	return (new_node);
}

void	add_exec_node(t_cmd *cmd, t_executor **exec_list)
{
	t_executor	*new_node;
	t_executor	*tmp_node;
	char		***temp;
	int			i;

	i = 0;
	temp = cmd->command;
	if (cmd->command == NULL || cmd->command[i] == NULL)
		return ;
	while (temp[i] != NULL)
	{
		new_node = create_exec_node(temp[i]);
		if (new_node == NULL)
		{
			g_globals_exit = 1;
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

char	**env_to_array(t_env *env_list)
{
	int		count;
	t_env	*temp;
	char	**env_array;
	char	*env_str;
	int		i;

	count = 0;
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
	i = 0;
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
