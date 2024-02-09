/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:12:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/09 13:52:21 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_bzero(void *s, size_t n)
{
	while (n && s)
		((char *)s)[--n] = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	alloc_mem_size;
	void	*ptr;

	if (nmemb && ((size_t)(-1) / nmemb) < size)
		return (0);
	alloc_mem_size = nmemb * size;
	ptr = (void *)malloc(alloc_mem_size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, alloc_mem_size);
	return (ptr);
}
