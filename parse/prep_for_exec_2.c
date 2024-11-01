/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:43:34 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/01 18:31:04 by kgulfida         ###   ########.fr       */
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

	i = 0;
	j = 0;
	cmd = malloc(sizeof(char *) * (len + 1));
	while (arg[i])
	{
		if(arg[i][0] == '\0')
			i++;
		if (i == 0)
		{
			if (check_redirect(arg[i]) == 1)
				i++;
			else
				cmd[j++] = ft_strdup(arg[i]);
		}
		else if(arg[i])
		{
			if (check_redirect(arg[i]) == 1)
				i++;
			else if (check_redirect(arg[i - 1]) == 0)
				cmd[j++] = ft_strdup(arg[i]);
		}
		if(arg[i])
			i++;
	}
	return (cmd);
}

static int	argv_len(char **argv)
{
	int	i;
	int	len;
	int	rdr;

	i = 0;
	rdr = 0;
	len = 0;
	while (argv[len])
		len++;
	while (argv[i])
	{
		if(argv[i][0] == '\0')
			len--;
		if (ft_strcmp(argv[i], ">") == 0 || ft_strcmp(argv[i], "<") == 0
			|| ft_strcmp(argv[i], ">>") == 0 || ft_strcmp(argv[i], "<<") == 0)
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

char	**clean_argv(t_cmd *cmd, char **str)
{
	int		i;
	int		j;
	char	**dest;
	char	*temp;
	int		len;

	len = 0;
	while (str[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	dest[len] = NULL;
	i = -1;
	j = 0;
	while (str[++i])
	{
		temp = ft_strtrim(str[i], " ,\t");
		dest[j++] = remove_quotes(cmd, temp);
		free(temp);
	}
	free_double(str);
	return (dest);
}
