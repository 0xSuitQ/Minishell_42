/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:27:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/19 19:48:04 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	freeing all 2D array. String by string
*/
void	free_arr(char **split_arr)
{
	int	i;

	i = -1;
	while (split_arr[++i])
		free(split_arr[i]);
	free(split_arr);
}
