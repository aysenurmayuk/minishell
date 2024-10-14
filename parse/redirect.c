/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/14 21:13:33 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Bağlı listeyi yazdırma fonksiyonu (debug için)
static void	print_redirect_list(t_redirect *redirect_list)
{
	while (redirect_list)
	{
		printf("%d = %s\n", redirect_list->type, redirect_list->filename);
		redirect_list = redirect_list->next;
	}
}

static t_redirect	*create_redirect_node(int type, char *filename)
{
	t_redirect	*new_node;

	new_node = malloc(sizeof(t_redirect));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->filename = ft_strdup(filename);
	new_node->next = NULL;
	return (new_node);
}

static void	add_redirect_node(t_redirect **redirects, int type, char *filename)
{
	t_redirect	*new;
	t_redirect	*temp;

	new = create_redirect_node(type, filename);
	if (!new)
		return ;
	if (!(*redirects))
		*redirects = new;
	else
	{
		temp = *redirects;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static char	*extract_filename(char *str)
{
	char	*filename;
	int		start;
	int		end;
	int		sq;
	int		dq;

	start = 0;
	sq = 0;
	dq = 0;
	while (str[start] && ft_isspace(str[start]))
		start++;
	end = start;
	while (str[end])
	{
		handle_quotes(str[end], &sq, &dq);
		if ((ft_isspace(str[end]) || str[end] == '|' || str[end] == '<'
				|| str[end] == '>') && sq % 2 == 0 && dq % 2 == 0)
			break ;
		end++;
	}
	filename = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!filename)
		return (NULL);
	strncpy(filename, str + start, end - start);
	filename[end - start] = '\0';
	return (filename);
}

static int	redirect_type(t_cmd *cmd, char *str, int k)
{
	int	type;

	(void)cmd;
	type = 0;
	if (str[k] == '>' && str[k + 1] == '>')
		type = APPEND;
	else if (str[k] == '<' && str[k + 1] == '<')
		type = HEREDOC;
	else if (str[k] == '>')
		type = OUTPUT;
	else if (str[k] == '<')
		type = INPUT;
	return (type);
}

static void	is_redirect(t_cmd *cmd, int *i, int *j, size_t d)
{
	int		sq;
	int		dq;
	int		type;
	char	*str;
	char	*filename;

	sq = 0;
	dq = 0;
	filename = NULL;
	str = cmd->command[*i][*j];
	while (str[d] != 0)
	{
		handle_quotes(str[d], &sq, &dq);
		if ((str[d] == '<' || str[d] == '>') && sq % 2 == 0 && dq % 2 == 0)
		{
			type = redirect_type(cmd, str, d);
			if (str[d + 1] == '<' || str[d + 1] == '>')
				d++;
			if (str[d + 1] != '\0')
			{
				if ((type == APPEND || type == HEREDOC) && str[d + 1] != '\0')
					filename = extract_filename(str + d + 1);
				else if ((type == OUTPUT || type == INPUT) && str[d
					+ 1] != '\0')
					filename = extract_filename(str + d + 1);
			}
			else
				filename = extract_filename(cmd->command[*i][*j + 1]);
			add_redirect_node(&cmd->redirect, type, remove_quotes(cmd,
					filename));
		}
		if (ft_strlen(str) <= d)
			break ;
		else
			d++;
	}
	cmd->command[*i][*j] = str;
}

void	redirect_handle(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->command[++i])
	{
		j = -1;
		while (cmd->command[i][++j])
			is_redirect(cmd, &i, &j, 0);
	}
}
