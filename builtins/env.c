/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:15:48 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/21 18:19:39 by kgulfida         ###   ########.fr       */
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

void	print_export_list(t_env *env_list)
{
	while (env_list)
	{
		printf("declare -x %s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
