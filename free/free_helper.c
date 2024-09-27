/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:45:22 by kgulfida          #+#    #+#             */
/*   Updated: 2024/09/27 14:47:24 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_dollar(char *dollar_before, char *dollar_after, char *dollar_value,
		char *line)
{
	free(line);
	free(dollar_before);
	free(dollar_after);
	free(dollar_value);
}
