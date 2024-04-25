/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:01 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/25 23:15:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	get_last_node is a function that will return the last node in the lexer list
*/
t_lexer	*get_last_node(t_lexer *list_head)
{
	if (list_head == NULL)
		return (NULL);
	while (list_head->next)
		list_head = list_head->next;
	return (list_head);
}

/**
	@brief:
	create_first_node is a function that will create the first node in the
	lexer list and fill it with the given parameters.
*/
static void	create_first_node(t_lexer **list, t_lexer *new_node)
{
	*list = new_node;
	(*list)->prev = NULL;
}

/**
	@brief:
	create_list is a function that will create a new node in the lexer list
	and fill it with the given parameters.
*/
void	create_list(t_lexer **list, int index, t_token_list tok, char *sub_str)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return ;
	if (*list == NULL)
		create_first_node(list, new_node);
	else
	{
		new_node->prev = get_last_node(*list);
		new_node->prev->next = new_node;
	}
	new_node->sub_str = ft_strdup(sub_str);
	new_node->index = index;
	new_node->token = tok;
	new_node->flag = VISIBLE;
	new_node->next = NULL;
}
