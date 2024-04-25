/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:02 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/25 23:12:32 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*ft_lexernew(char *str, t_token_list token)
{
	t_lexer		*new_element;
	static int	i = 0;

	new_element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_element)
		return (0);
	new_element->sub_str = ft_strdup(str);
	new_element->token = token;
	new_element->index = i++;
	new_element->flag = VISIBLE;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	add_node(char *str, t_token_list token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = ft_lexernew(str, token);
	if (!node)
		return (0);
	ft_lexeradd_back(lexer_list, node);
	return (1);
}

int	read_words(int i, char *str, t_lexer **lexer_list)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += handle_quotes(i + j, str, '\"');
		j += handle_quotes(i + j, str, '\'');
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
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
