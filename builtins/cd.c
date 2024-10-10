#include "../minishell.h"

static void update_env_var(t_env **env_list, char *key, char *value) 
{
    t_env *tmp;

    tmp = *env_list;
    while (tmp) 
    {
        if (ft_strcmp(tmp->key, key) == 0) 
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }
    add_env_node(env_list, key, value);
}

void ft_cd(t_cmd *cmd) 
{
    char *oldpwd = NULL;
    char cwd[1024];

    oldpwd = get_env(cmd, "PWD", NULL);
    if (!cmd->command[0][1]) {
        char *home = get_env(cmd, "HOME", NULL);
        if (home) {
            if (chdir(home) != 0) {
                printf("cd: %s: %s\n", home, strerror(errno));
            }
        }
    } else {
        if (chdir(cmd->command[0][1]) != 0) {
            printf("cd: %s: %s\n", cmd->command[0][1], strerror(errno));
        }
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        update_env_var(&(cmd->env), "OLDPWD", oldpwd);
        update_env_var(&(cmd->env), "PWD", cwd);
    } else {
        printf("cd: error retrieving current directory: %s\n", strerror(errno));
    }
    free(oldpwd);
}
