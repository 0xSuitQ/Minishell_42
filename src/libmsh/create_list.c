/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:01 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/14 18:49:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*get_last_node(t_lexer *list_head)
{
	if (list_head == NULL)
		return (NULL);
	while (list_head->next)
		list_head = list_head->next;
	return (list_head);
}

static void	create_first_node(t_lexer **list, t_lexer *new_node)
{
	*list = new_node;
	(*list)->prev = NULL;
}

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
	new_node->sub_str = ft_strdup(sub_str); // TODO: mind to freeing it
	new_node->index = index;
	new_node->token = tok;
	new_node->flag = VISIBLE;
	new_node->next = NULL;
}
