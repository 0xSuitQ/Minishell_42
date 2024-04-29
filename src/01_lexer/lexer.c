/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:02 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/29 20:35:49 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_words(int i, char *str, t_lexer **lexer_list)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += handle_quotes(i + j, str, '\'');
		j += handle_quotes(i + j, str, '\"');
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	if (j == 0)
    	return (0); 
	tmp = ft_substr(str, i, j);
	if (!add_node(tmp, 0, lexer_list))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (j);
}

int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_token_list	token;

	token = check_token(str[i]);
	if (token == GREAT && check_token(str[i + 1]) == GREAT)
	{
		if (!add_node(NULL, GREAT_GREAT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_token(str[i + 1]) == LESS)
	{
		if (!add_node(NULL, LESS_LESS, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief:
   Lexer goes through user's input, tokenize it and store it in a lexer list.
   This lexer list contains tokens representing words, operators (like |, <, 
   >, etc.), and other special characters.
   It goes through the input string and tokenizes it based on the
   @param tools: pointer to the main_tools structure
*/
int	lexer(t_main_tools *tools)
{
	int		i;
	int		j;

	i = 0;
	while (tools->args && tools->args[i])
	{
		j = 0;
		i += skip_spaces(tools->args, i);
		if (check_token(tools->args[i]))
			j = handle_token(tools->args, i, &tools->lexer_list);
		else
			j = read_words(i, tools->args, &tools->lexer_list);
		if (j < 0)
			return (EXIT_FAILURE);
		i += j;
	}
	return (EXIT_SUCCESS);
}
