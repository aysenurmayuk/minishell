/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/30 17:36:38 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*extract_filename(char *str, int sq, int dq)
{
	char	*filename;
	int		start;
	int		end;

	start = 0;
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
	ft_strncpy(filename, str + start, end - start);
	filename[end - start] = '\0';
	return (filename);
}

static int	redirect_type(char *str, int r)
{
	int	type;

	type = 0;
	if (str[r] == '>' && str[r + 1] == '>')
		type = APPEND;
	else if (str[r] == '<' && str[r + 1] == '<')
		type = HEREDOC;
	else if (str[r] == '>')
		type = OUTPUT;
	else if (str[r] == '<')
		type = INPUT;
	return (type);
}

static void	is_redirect(t_cmd *cmd, t_executor *temp, int *i, int *j, size_t r)
{
	int		sq;
	int		dq;
	int		type;
	char	*str;
	char	*filename;

	sq = 0;
	dq = 0;
	str = cmd->command[*i][*j];
	filename = NULL;
	while (str[r] != 0)
	{
		handle_quotes(str[r], &sq, &dq);
		if ((str[r] == '<' || str[r] == '>') && sq % 2 == 0 && dq % 2 == 0)
		{
			type = redirect_type(str, r);
			filename = extract_filename(cmd->command[*i][*j + 1], 0, 0);
			add_redirect_node(&temp->redirect, type, remove_quotes(cmd,
					filename));
			r++;
		}
		if (ft_strlen(str) <= r)
			break ;
		r++;
	}
}

void	redirect_handle(t_cmd *cmd, t_executor *temp, int *i)
{
	int	j;

	j = -1;
	while (cmd->command[*i][++j])
		is_redirect(cmd, temp, i, &j, 0);
}
