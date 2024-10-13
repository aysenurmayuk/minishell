/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:14:08 by kgulfida          #+#    #+#             */
/*   Updated: 2024/10/13 15:12:18 by amayuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)str;
	while (i < n)
	{
		dest[i] = c;
		i++;
	}
	return (str);
}
