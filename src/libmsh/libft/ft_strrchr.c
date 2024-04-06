/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:43:07 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/06 17:57:03 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
	@param:
		last_occur_char: pointer to the last occurrence of the character in the
		string
*/
char	*ft_strrchr(const char *str, int character)
{
	int		i;
	char	*last_occur_char;

	i = -1;
	last_occur_char = 0;
	while (str[++i])
		if (str[i] == character % 256)
			last_occur_char = (char *) &str[i];
	if (str[i] == character % 256)
		last_occur_char = (char *) &str[i];
	return (last_occur_char);
}
