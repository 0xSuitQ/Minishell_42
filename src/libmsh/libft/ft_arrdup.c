/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:00:09 by peta              #+#    #+#             */
/*   Updated: 2024/04/23 18:02:08 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_elems(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **src)
{
	int		i;
	char	**dst;
	int		j;
	int		k;

	j = 0;
	k = 0;
	i = count_elems(src);
	dst = malloc((i + 1) * sizeof(char *));
	if (dst == NULL)
		return (NULL);
	while (j < i)
	{
		dst[j] = ft_strdup(src[j]);
		if (dst[j] == NULL)
		{
			while (k < j)
				free(dst[k++]);
			free(dst);
			return (NULL);
		}
		j++;
	}
	dst[i] = NULL;
	return (dst);
}
