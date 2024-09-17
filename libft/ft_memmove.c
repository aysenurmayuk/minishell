/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:42:40 by kgulfida          #+#    #+#             */
/*   Updated: 2023/12/11 13:57:49 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest1;

	dest1 = (unsigned char *)dest;
	if (!dest && !src)
		return (dest);
	if (dest == src)
		return (dest);
	else if (dest > src)
	{
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	else
	{
		while (n--)
		{
			*(unsigned char *)dest = *(unsigned char *)src;
			dest++;
			src++;
		}
	}
	return (dest1);
}
