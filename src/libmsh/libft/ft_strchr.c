/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:51:28 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/06 18:10:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
    @brief:
    Locates the first occurrence of the character in the string
    returns a pointer to the located character
*/
char	*ft_strchr(const char *str, int character)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == character % 256)
			return ((char *) &str[i]);
	if (str[i] == character % 256)
		return ((char *) &str[i]);
	return (0);
}
