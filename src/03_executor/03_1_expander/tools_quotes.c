/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:46:40 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 19:16:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
	@brief:
	remove_quotes function removes the quotes from the string
	- it goes through the string and if there is a quote, it will be removed
	both: at the beggining and at the end
	@param:
	- str: string from which the quotes will be removed
	- quote_type: type of the quote, which will be removed
*/
void	remove_quotes(char *str, char quote_type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
		{
			j = 1;
			while (str[i + j] != quote_type)
				j++;
			ft_strlcpy(&str[i], &str[i + 1], j);
			break ;
		}
		i++;
	}
}

/**
	@brief:
	quotes_classifier function classifies the quotes in the string
	- if there is a single quote, it returns SINGLE_Q
	- if there is a double quote, it returns DOUBLE_Q
	- if there are no quotes, it returns NO_Q
*/
int	quotes_classifier(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (SINGLE_Q);
		if (str[i] == '\"')
			return (DOUBLE_Q);
		i++;
	}
	return (NO_Q);
}

/**
	@brief:
	handle_dollar function handles the dollar sign in the string
	it goes through the string and if there is a $, it will be expanded
*/
int	there_is_single_quote(char *str)
{
	if (quotes_classifier(str) == SINGLE_Q)
	{
		remove_quotes(str, '\'');
		return (TRUE);
	}
	return (FALSE);
}
