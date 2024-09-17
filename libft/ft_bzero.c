/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:17:09 by kgulfida          #+#    #+#             */
/*   Updated: 2023/12/07 19:17:37 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = str;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
	return (str);
}
