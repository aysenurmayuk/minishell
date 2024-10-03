#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int i;
	int n;

	n = 1;
	i = 1; 
	if (cmd->command[0][i] && ft_strcmp(cmd->command[0][i], "-n") == 0)
	{
		n = 0;
		i++;
	}
	while (cmd->command[0][i])
	{
		printf("%s", cmd->command[0][i]);
		if (cmd->command[0][i + 1])
			printf(" ");
		i++;
	}
	if (n)
		printf("\n");
}
