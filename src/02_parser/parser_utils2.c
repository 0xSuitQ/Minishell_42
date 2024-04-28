/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:30:36 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/28 19:15:57 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	count_pipes function counts the number of pipes in the lexer_list. And
	returns the number (count) of pipes.
*/
int	count_pipes(t_lexer *lexer_list)
{
	int		count;
	t_lexer	*tmp;

	count = 0;
	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->token == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/**
	@brief:
	connect_node_to_list function connects the new_node to the list of
	simple_cmd structures.
*/
void	connect_node_to_list(t_simple_cmd **list, t_simple_cmd *new_node)
{
	new_node->prev = get_last_cmd_node(list);
	new_node->prev->next = new_node;
}

/**
	@brief:
	simple function count_args function counts the number of arguments in
	the lexer_list. It is used to allocate the right amount of memory in the
	init_simple_cmd function. It ends when it reaches the end of the list or
	when it encounters a pipe.
*/
int	count_args(t_lexer *lexer_list)
{
	int	counter;

	counter = 0;
	while (lexer_list && lexer_list->token != PIPE)
	{
		if (lexer_list->index >= 0)
			counter++;
		lexer_list = lexer_list->next;
	}
	return (counter);
}

/**
	@brief:
	get_last_cmd_node function returns the last node of the list of
	simple_cmd structures. It uses tmp variable to go through the list without
	changing the head of the list in the functions that call it.
*/
t_simple_cmd	*get_last_cmd_node(t_simple_cmd **lexer_list)
{
	t_simple_cmd	*tmp;

	tmp = *lexer_list;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
	@brief:
	first_node_not_pipe function checks if the first node is a pipe. If it
	is, it prints an error message and exits the program.
*/
void	first_node_not_pipe(t_lexer *lex_head, t_main_tools *tools)
{
	if (!lex_head)
		return ;
	if (lex_head->token == PIPE)
		unexpected_token_officer(lex_head, tools);
}
