/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:15:48 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/30 16:13:20 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// Yeni bir ortam değişkeni düğümü oluşturma fonksiyonu
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

// Bağlı listeye bir düğüm ekleme fonksiyonu
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

	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		delimiter = ft_strchr(envp[i], '=');
		if (delimiter)
		{
			key = ft_strndup(remove_quotes(cmd, envp[i]), delimiter - envp[i]);
			value = ft_strdup(remove_quotes(cmd, delimiter + 1));
			add_env_node(env_list, key, value);
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
