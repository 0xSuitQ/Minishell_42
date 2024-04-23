/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   there_is_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:44:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/22 19:22:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
	@brief:
	there_is_dollar function checks if there is a dollar sign in the string
	- if there is a dollar sign, it returns 1 = TRUE
	- if there is no dollar sign, it returns 0 = FALSE
*/
int	there_is_dollar_in_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (TRUE);
	return (FALSE);
}

/**
	@brief:
	dollar_in_list function checks if there is a dollar sign in the list
	- if there is a dollar sign, it returns 1 = TRUE
	- if there is no dollar sign, it returns 0 = FALSE
*/
int	there_is_dollar_in_list(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		if (there_is_dollar_in_str(list[i]))
			return (TRUE);
	return (FALSE);
}

/**
	@brief:
	- next_dollar function finds the next dollar sign in the string
	- if there is a dollar sign, it returns the index of the dollar sign
	- if there is no dollar sign, it returns the length of the string
*/
int	next_dollar(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (i);
	return (i);
}

/**
	@brief:
	num_of_dollars_in_list function counts the number of dollar signs in the
	list for proper allocation of memory
*/
int	num_of_dollars_in_list(char **str)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
		if (there_is_dollar_in_str(str[i]))
			count++;
	return (count);
}
