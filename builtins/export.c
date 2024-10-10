#include "../minishell.h"

void	ft_export(t_env **env_list, char *key_value)
{
	char	*delimiter;
	char	*key;
	char	*value;
	t_env	*current;

	delimiter = ft_strchr(key_value, '=');
	if (!delimiter)
	{
		printf("export: '%s': not a valid identifier\n", key_value);
		return; // belki sileriz denemek için
	}
	key = ft_strndup(key_value, delimiter - key_value);
	value = ft_strdup(delimiter + 1);
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			free(key);
			return;
		}
		current = current->next;
	}
	add_env_node(env_list, key, value);
}


