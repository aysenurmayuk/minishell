/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:43:34 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/31 21:42:57 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_redirect(char *arg)
{
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0 || ft_strcmp(arg,
			"<<") == 0 || ft_strcmp(arg, ">>") == 0)
		return (1);
	else
		return (0);
}

static char	**find_argv(char **arg, int len)
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
			if (check_redirect(arg[i]) == 1)
				i++;
			else
				cmd[j++] = ft_strdup(arg[i]);
		}
		else
		{
			if (check_redirect(arg[i]) == 1)
				i++;
			else if (check_redirect(arg[i - 1]) == 0)
				cmd[j++] = ft_strdup(arg[i]);
		}
	}
	return (cmd);
}

static int	argv_len(char **arg)
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

	len = argv_len(arg);
	cmd = find_argv(arg, len);
	cmd[len] = NULL;
	return (cmd);
}

char	**clean_argv(char **str)
{
	int		i;
	int		j;
	char	**dest;
	int		len;

	len = 0;
	while (str[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	dest[len] = NULL;
	i = -1;
	j = 0;
	while (str[++i])
		dest[j++] = ft_strdup(str[i]);
	free_double(str);
	return (dest);
}
