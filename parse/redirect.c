/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:34:59 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/21 19:43:22 by kgulfida         ###   ########.fr       */
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
	strncpy(filename, str + start, end - start);
	filename[end - start] = '\0';
	return (filename);
}

static int	redirect_type(t_cmd *cmd, char *str, int r)
{
	int	type;

	(void)cmd;
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

static void	is_redirect(t_cmd *cmd, int *i, int *j, size_t r)
{
	int		sq;
	int		dq;
	int		type;
	char	*str;
	char	*filename;

	sq = 0;
	dq = 0;
	type = 0;
	filename = NULL;
	str = cmd->command[*i][*j];
	while (str[r] != 0)
	{
		handle_quotes(str[r], &sq, &dq);
		if ((str[r] == '<' || str[r] == '>') && sq % 2 == 0 && dq % 2 == 0)
		{
			type = redirect_type(cmd, str, r);
			if (str[r + 1] == '<' || str[r + 1] == '>')
				r++;
			if (str[r + 1] != '\0')
				filename = extract_filename(str + r + 1, 0, 0);
			else
				filename = extract_filename(cmd->command[*i][*j + 1], 0, 0);
			add_redirect_node(&cmd->redirect, type, remove_quotes(cmd,
						filename));
		}
		if (ft_strlen(str) <= r)
			break ;
		r++;
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
		if (cmd->redirect != NULL)
			cmd->executor->files = init_redirect(cmd, cmd->executor->files);
	}
}
