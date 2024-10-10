#include "../minishell.h"

void ft_unset(t_env **env_list, char *key)
{
    t_env *current = *env_list;
    t_env *previous = NULL;

    while (current) {
        if (ft_strcmp(current->key, key) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                *env_list = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
