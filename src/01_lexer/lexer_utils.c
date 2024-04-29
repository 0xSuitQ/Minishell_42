/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:12:19 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/29 20:40:19 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(int i, char *str, char quote)
{
	int	j;

	j = 0;
	if (str[i] == quote)
	{
		i++;
		while (str[i + j] && str[i + j] != quote)
			j++;
		if (str[i + j] == quote)
			j++;
	}
	return (j);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}

t_token_list	check_token(int c)
{
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', GREAT},
	{'<', LESS},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (EXIT_SUCCESS);
}
