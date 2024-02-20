/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substring_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:50:39 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/12 09:54:34 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	substring_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		if (str[i])
			counter++;
		while (str[i] && (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32)))
			i++;
	}
	return (counter);
}
