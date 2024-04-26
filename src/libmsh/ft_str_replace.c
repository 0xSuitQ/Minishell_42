/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:51:06 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/26 16:35:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	- ft_str_replace function replaces the string with the new string
	- it allocates memory for the new string, copies the new string into it
	and frees the old string
*/
void	ft_str_replace(char **str, char *result)
{
	char *new_str;

	if (str == NULL || *str == NULL || result == NULL)
		return ;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(result) + 1);
	if (new_str == NULL)
		return ;
	ft_strcpy(new_str, result);
	// free(*str);
	*str = new_str;
}
