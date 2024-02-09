/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:09:33 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/07 17:47:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_arrdup(char **arr)
{
	char			**output_arr;
	static size_t	i = 0;
	static int		j = -1;

	while (arr[i])
		i++;
	output_arr = ft_calloc(i + 1, sizeof(char *));
	if (!output_arr)
		return (NULL);
	while (arr[++j])
	{
		output_arr[j] = ft_strdup(arr[j]);
		if (!output_arr[j])
		{
			free_arr(output_arr);
			return (output_arr);
		}
	}
	return (output_arr);
}
