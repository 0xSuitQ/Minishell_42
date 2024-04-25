/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_sepdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:48:40 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/25 23:17:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	ft_str_sep_len is a function that will return the length of the string
	until the first separator
*/
static	int	ft_str_sep_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	return (i);
}

/**
	@brief:
	ft_str_sepdup is a function that will duplicate the string until the first
	separator
*/
char	*ft_str_sepdup(char *s)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = ft_str_sep_len(s);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
