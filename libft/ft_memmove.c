/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayuk <amayuk@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:18:53 by amayuk            #+#    #+#             */
/*   Updated: 2023/12/26 14:37:05 by amayuk           ###   ########.fr       */
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
