/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:15:48 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/04 17:33:48 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_env_node(key, value);
	temp = *env_list;
	if (!new_node)
		return ;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	parse_env(t_cmd *cmd, char **envp, t_env **env_list)
{
	int		i;
	char	*key;
	char	*value;
	char	*delimiter;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		delimiter = ft_strchr(envp[i], '=');
		if (delimiter)
		{
			temp = remove_quotes(cmd, envp[i]);
			key = ft_strndup(temp, delimiter - envp[i]);
			value = remove_quotes(cmd, delimiter + 1);
			add_env_node(env_list, key, value);
			free(temp);
		}
		i++;
	}
}

void	print_env_list(t_cmd *cmd, t_env *env_list, t_executor *executor)
{
	char	*key;
	char	*value;
	int		fd;

	fd = executor->files->fd_output;
	while (env_list)
	{
		key = remove_quotes(cmd, env_list->key);
		value = remove_quotes(cmd, env_list->value);
		write(fd, key, ft_strlen(key));
		write(fd, "=", 1);
		write(fd, value, ft_strlen(value));
		write(fd, "\n", 1);
		free(key);
		free(value);
		env_list = env_list->next;
	}
	cmd->status = 0;
}

char	*get_env(t_cmd *cmd, char *key, char *dollar_value)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			dollar_value = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!dollar_value)
		dollar_value = ft_strdup("");
	return (dollar_value);
}
