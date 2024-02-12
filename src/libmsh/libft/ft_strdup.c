/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:52:28 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/12 09:53:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*str;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
