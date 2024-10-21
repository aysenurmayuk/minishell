/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:56:16 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/19 15:56:47 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_line(int fd, char *buffer, char *stack)
{
	int		read_byte;
	char	*temp;

	while (1)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (0);
		else if (read_byte == 0)
			break ;
		buffer[read_byte] = '\0';
		if (!stack)
			stack = ft_strdup("");
		temp = stack;
		stack = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stack);
}

static char	*clean_stack(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (str == NULL)
		return (NULL);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stack[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, stack[fd]);
	free(buffer);
	if (line == NULL)
	{
		stack[fd] = NULL;
		return (NULL);
	}
	stack[fd] = clean_stack(line);
	return (line);
}
