/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:43:41 by kgulfida          #+#    #+#             */
/*   Updated: 2023/12/11 14:25:29 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	void	*memory;

	memory = (void *)malloc(count * n);
	if (!memory)
		return (0);
	ft_bzero(memory, (count * n));
	return (memory);
}
