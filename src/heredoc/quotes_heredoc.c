/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:32:56 by peta              #+#    #+#             */
/*   Updated: 2024/04/30 11:33:54 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	delete_quotes is a function that will delete the quotes from the string
*/
char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], j + 1);
		}
	}
	return (str);
}

/**
	@brief:
	quote_check is a function that will check if the delimiter is a quote
	and delete the quotes from the delimiter
*/
void	quote_check(char **delimiter)
{
	if ((*delimiter)[0] == '\'' || (*delimiter)[0] == '\"')
	{
		delete_quotes((*delimiter), '\'');
		delete_quotes((*delimiter), '\"');
	}
}
