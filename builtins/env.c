/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysenurmayuk <aysenurmayuk@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:15:48 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/10 19:08:37 by aysenurmayu      ###   ########.fr       */
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

// Ortam değişkenlerini ayırma ve listeye ekleme fonksiyonu
void	parse_env(char **envp, t_env **env_list)
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
			key = ft_strndup(envp[i], delimiter - envp[i]);
			value = ft_strdup(delimiter + 1);
			add_env_node(env_list, key, value);
		}
		i++;
	}
}

// Bağlı listeyi yazdırma fonksiyonu (debug için)
void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
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

// EXPORT'A EKLENECEK
void	print_export_list(t_env *env_list)
{
	while (env_list)
	{
		printf("declare -x %s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
