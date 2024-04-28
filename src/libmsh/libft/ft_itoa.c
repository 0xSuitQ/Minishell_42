/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:12:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 18:47:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	determine_length(long long n, int neg_or_pos)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	if (neg_or_pos)
		i++;
	return (i);
}

char	*fill_arr(long long n, char *arr, int i, int neg_or_pos)
{
	arr[i] = '\0';
	i--;
	if (n == 0)
	{
		arr[i] = '0';
		i--;
	}
	while (n > 0)
	{
		arr[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	if (neg_or_pos)
	{
		arr[i] = '-';
		i++;
	}
	return (arr);
}

char	*ft_itoa(int n)
{
	int			i;
	int			neg_or_pos;
	char		*arr;
	long long	j;

	neg_or_pos = 0;
	if (n < 0)
	{
		neg_or_pos = 1;
		j = (long long)n * -1;
	}
	else
		j = (long long)n;
	i = determine_length(j, neg_or_pos);
	arr = malloc(i * sizeof(char) + 1);
	if (!arr)
		return (0);
	arr = fill_arr(j, arr, i, neg_or_pos);
	return (arr);
}
