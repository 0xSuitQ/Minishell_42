/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/20 18:06:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*s1_2;
	int		i;

	if ((!s1 || !s2) || (!s1 && !s2))
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	s1_2 = (char *)malloc(len * sizeof(char) + 1);
	i = 0;
	if (!s1_2)
		return (0);
	while (*s1)
	{
		s1_2[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		s1_2[i] = *s2;
		s2++;
		i++;
	}
	s1_2[i] = '\0';
	return (s1_2);
}