/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:43:34 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 16:47:40 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_redirect(char *arg)
{
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0
		|| ft_strcmp(arg, "<<") == 0 || ft_strcmp(arg, ">>") == 0)
		return (1);
	else
		return (0);
}

char	**ft_find_cmd(char **arg, int len)
{
	int		i;
	char	**cmd;
	int		j;

	i = -1;
	j = 0;
	cmd = malloc(sizeof(char *) * (len + 1));
	while (arg[++i])
	{
		if (i == 0)
		{
			if (ft_check_redirect(arg[i]) == 1)
				i++;
			else
				cmd[j++] = ft_strdup(arg[i]);
		}
		else
		{
			if (ft_check_redirect(arg[i]) == 1)
				i++;
			else if (ft_check_redirect(arg[i -1]) == 0)
				cmd[j++] = ft_strdup(arg[i]);
		}
	}
	return (cmd);
}

int	ft_cmd_len(char **arg)
{
	int	i;
	int	len;
	int	rdr;

	i = 0;
	rdr = 0;
	len = 0;
	while (arg[i++])
		len++;
	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], "<") == 0
			|| ft_strcmp(arg[i], ">>") == 0 || ft_strcmp(arg[i], "<<") == 0)
			rdr++;
		i++;
	}
	return (len - (rdr * 2));
}

char	**fill_argv(char **arg)
{
	int		len;
	char	**cmd;

	len = ft_cmd_len(arg);
	cmd = ft_find_cmd(arg, len);
	cmd[len] = NULL;
	return (cmd);
}